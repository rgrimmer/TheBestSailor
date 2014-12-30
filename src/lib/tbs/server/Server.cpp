/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <bitset>

#include "shared/network/MsgGame.h"
#include "shared/network/MsgClientPlayerInfo.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/MsgAction.h"
#include "shared/network/MsgData.h"
#include "shared/network/UtilsNetwork.h"

#include "server/game/ServerGame.h"
#include "server/game/ServerGameSpeedestWin.h"
#include "server/network/ServerMessageQueue.h"
#include "server/ServerPlayer.h"
#include "server/Server.h"

Server::Server()
: m_game(nullptr)
, m_network(m_players)
, m_readerThread(nullptr)
, m_threadRun(false) {

}

Server::~Server() {
}

void Server::start() {
    srand(time(NULL));

    initializeNetwork();

    while (true) {
        startChronoAndWait();
        createGame();
        sendGame();
        startGame();
    }
}

void Server::initializeNetwork() {
    m_network.initialize();
}

void Server::startChronoAndWait() {
    sf::Time timeoutWaitPlayers = sf::milliseconds(5000);

    // Main loop, game can't start without player
    do {
        std::cout << "[Serv][WaitP] \tWait players" << std::endl;
        // Wait first player
        while (m_players.inWait().empty()) {
            readMessagesWait();
            if (m_players.size() < 1)
                std::cout << "[Serv][WaitP] \tFirst connection, start chrono" << std::endl;
            else
                std::cout << "[Serv][WaitP] \t Warning, expect new client" << std::endl;
        }

        sf::Clock clockWaitPlayers;

        while (clockWaitPlayers.getElapsedTime() < timeoutWaitPlayers) {
            if (m_players.inWait().empty())
                break;
            readMessagesWait(timeoutWaitPlayers - clockWaitPlayers.getElapsedTime());
        }
    } while (m_players.inWait().empty());
}

void Server::createGame() {
    std::cout << "[Create] \tGame" << std::endl;
    // @TODO : switch with different game type
    m_game = new ServerGameSpeedestWin(*this, m_players, MapHeader(200, 200, 42));
}

void Server::sendGame() {
    std::cout << "[Broad] \tGame" << std::endl;
    MsgData msgGame;
    msgGame << MsgType::Game << GameType::SpeedestWin << sf::Int32(200) << sf::Int32(200) << sf::Int32(42) << sf::Int32(42);

    m_network.getTCPManager().send(msgGame, std::vector<ServerPlayer*>(m_players.inGame().begin(), m_players.inGame().end()));
    waitAcknowledgment(m_players.inGame().size());
}

void Server::startGame() {
    m_game->start();
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
    if (m_game)
        isRead = m_game->read(messageCopy, player);

    message >> msgType;
    std::cout << "[Serv][Read][Start] \t Read message(" << static_cast<int> (msgType) << ") from " << player.getName() << std::endl;
    switch (msgType) {
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
            MsgData msgServer;
            msgServer << MsgType::ServerPlayerInfo << sf::Uint16(SERVER_PORT_UDP) << sf::Int16(player.getId());
            std::cout << "[Serv][Read] \t Send info serv. ServUdpPort(" << SERVER_PORT_UDP << "), playerId(" << sf::Int16(player.getId()) << ")" << std::endl;
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

void Server::waitAcknowledgment(int permits) {

    m_acknowledgment.aquire(permits);
}

ServerNetwork* Server::getNetwork() {
    return &m_network;
}

