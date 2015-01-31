/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>
#include <bitset>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "shared/Utils.h"
#include "shared/ship/Ship.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MsgClientPlayerInfo.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/MsgAction.h"
#include "shared/network/MsgData.h"

#include "server/game/ServerGame.h"
#include "server/game/ServerGameSpeedestWin.h"
#include "server/network/ServerMessageQueue.h"
#include "server/ServerPlayer.h"
#include "server/Server.h"

Server::Server()
: m_game(nullptr)
, m_network(m_players)
, m_readerThread(nullptr)
, m_threadRun(false)
, m_stateInWait(true) {

}

Server::~Server() {
}

void Server::start(unsigned short portConnection) {
    srand(time(NULL));

    initializeNetwork(portConnection);

    while (true) {
        startChronoAndWait();
        createGame();
        sendGame();
        startGame();
    }
}

void Server::initializeNetwork(unsigned short portConnection) {
    m_network.initialize(portConnection);
}

void Server::startChronoAndWait() {
    m_stateInWait = true;

    // Main loop, game can't start without player
    do {

        std::cout << "[Serv][WaitP] \tWait players" << std::endl;
        // Wait first player
        while (m_players.inWait().empty()) {
            readMessagesWait();
            if (m_players.inWait().size() >= 1)
                std::cout << "[Serv][WaitP] \tFirst connection, start chrono" << std::endl;
            else
                std::cout << "[Serv][WaitP] \t Warning, expect new client" << std::endl;
        }
        std::cout << "[Serv][WaitP] \tStart chrono" << std::endl;

        sf::Time timeoutWaitPlayers = sf::milliseconds(20000);
        sendWaitTimeLeft(timeoutWaitPlayers.asSeconds());

        sf::Clock clockWaitPlayers;

        while (timeoutWaitPlayers > sf::Time::Zero && m_stateInWait) {
            if (m_players.inWait().empty())
                break;
            bool hasRead = readMessagesWait(timeoutWaitPlayers);
            timeoutWaitPlayers -= clockWaitPlayers.restart();
            if (hasRead) {
                sendWaitTimeLeft(timeoutWaitPlayers.asSeconds());
            }
        }
    } while (m_players.inWait().empty() && m_stateInWait);
    m_stateInWait = false;
}

void Server::createGame() {
    std::cout << "[Create] \tGame" << std::endl;
    // @TODO : switch with different game type
    m_game = new ServerGameSpeedestWin(*this, m_players, MapHeader(NB_TILES_HEIGHT, NB_TILES_WIDTH, rand()));
}

void Server::sendGame() {
    std::cout << "[Broad] \tGame" << std::endl;
    m_game->sendGame();
    waitAcknowledgment(m_players.inGame().size());
}

void Server::startGame() {
    m_game->start();
}

void Server::sendWaitTimeLeft(float timeLeft) {
    MsgData msg;
    msg << MsgType::TimeLeft << timeLeft;
    m_network.getTCPManager().send(msg, m_players.inWait());
}

void Server::startReaderThread() {
    m_readerThread = new std::thread(&Server::readerLoop, this);
}

void Server::stopReaderThread() {
    m_threadRun = false;
}

void Server::readerLoop() {
    // Wile game is not ended, we read messages. And check ended each 5s
    m_threadRun = true;
    while (m_threadRun) {
        // If we read somthing, we update world
        readMessagesWait(sf::milliseconds(5000));
    }
}

bool Server::readMessagesWait(sf::Time timeout) {
    //std::cout << "[Serv][PollM][Start] \t Poll messages started (With wait)" << std::endl;
    if (m_network.getMessageQueue().empty())
        if (!m_network.getMessageQueue().waitEvent(timeout)) {
            //std::cout << "[Serv][PollM][End] \t Poll messages ended (With timeout)" << std::endl;
            return false;

        }
    pollMessages();
    //std::cout << "[Serv][PollM][End] \t Poll messages ended (With receive message)" << std::endl;
    return true;
}

void Server::pollMessages() {
    //    std::cout << "[Serv][PollM][Start] \t Poll messages started" << std::endl;
    while (!m_network.getMessageQueue().empty()) {
        auto pair = m_network.getMessageQueue().pop();
        read(*(pair.second), *(pair.first));
        delete pair.second;
    }
    //    std::cout << "[Serv][PollM][End] \t Poll messages ended" << std::endl;
}

bool Server::read(MsgData& message, ServerPlayer &player) {
    MsgType msgType;
    MsgData messageCopy(message);

    bool isRead(false);

    message >> msgType;
    std::cout << "[Serv][Read][Start] \t Read message(" << static_cast<int> (msgType) << ") from " << player.getName() << std::endl;
    switch (msgType) {
        case MsgType::Action:
            if (m_stateInWait)
                return readAction(message, player);
            break;
        case MsgType::ClientPlayerInfo:
        {
            // Receive info from Client
            std::cout << "[Serv][Read] \t Read ClientPlayerInfo" << std::endl;
            //            auto msgCPI = static_cast<MsgClientPlayerInfo> (*message);
            sf::Uint16 sfPort;
            std::string name;
            message >> sfPort >> name;
            //            std::cout << "[Serv][Read] \t cast done : " << msgCPI << std::endl;
            player.setUdpPort(sfPort);
            player.setName(name);
            std::cout << "[Serv][Read] \t Read info client(" << player.getName() << "@" << player.getAddress().toString() << ":" << player.getUdpPort() << ")" << std::endl;
            // Send info to Client

            unsigned short port = m_network.getUDPManager().getPort();
            MsgData msgServer;
            msgServer << MsgType::ServerPlayerInfo << sf::Uint16(port) << sf::Int16(player.getId());
            std::cout << "[Serv][Read] \t Send info serv. ServUdpPort(" << port << "), playerId(" << sf::Int16(player.getId()) << ")" << std::endl;
            m_network.getTCPManager().send(msgServer, player.getTCPSocket());
            m_players.setPlayerReady(player);
            isRead = true;
        }
            break;
        case MsgType::Acknowledgment:
        {
            std::cout << "Ack" << std::endl;
            m_acknowledgment.release();
            isRead = true;
        }
            break;
        case MsgType::Disconnect:
        {
            isRead |= readDisconnect(message, player);
        }
            break;
        case MsgType::Undef:
        {
            std::cout << "Undefined" << std::endl;
        }
            break;
        default:
        {
        }
    }

    if (m_game)
        isRead = m_game->read(messageCopy, player);

    return isRead;
}

bool Server::readDisconnect(MsgData& msg, ServerPlayer& player) {
    std::cout << "Disconnect" << std::endl;
    auto idPlayer = static_cast<sf::Uint8> (player.getId());

    m_players.remove(player);

    MsgData msgDisconnect;
    msgDisconnect << MsgType::Disconnect << idPlayer;
    m_network.getTCPManager().send(msgDisconnect, m_players.getList());

    return true;
}

bool Server::readAction(MsgData& msg, ServerPlayer& player) {
    std::cout << "[Read] \tRead actions !!!!" << std::endl;
    sf::Int16 action;
    msg >> action;
    switch (action) {
        case sf::Keyboard::Key::Left:
            player.setIdShip((player.getShipType() + Ship::maxType - 1) % Ship::maxType);
            break;

        case sf::Keyboard::Key::Right:
            player.setIdShip((player.getShipType() + 1) % Ship::maxType);
            break;
            
        case sf::Keyboard::G:
            m_stateInWait = false;
            break;
            
        default:
            std::cout << "unused action" << std::endl;
            break;
    }
    return true;
}

void Server::waitAcknowledgment(int permits) {

    m_acknowledgment.aquire(permits);
}

ServerNetwork* Server::getNetwork() {
    return &m_network;
}

