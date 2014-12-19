/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "shared/network/MsgGame.h"
#include "shared/network/MsgClientPlayerInfo.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/MessageData.h"
#include "shared/network/UtilsNetwork.h"

#include "server/game/ServerGame.h"
#include "server/game/ServerGameSpeedestWin.h"
#include "server/network/ServerMessageQueue.h"
#include "server/ServerPlayer.h"
#include "server/Server.h"

Server::Server()
: m_game(nullptr)
, m_network(m_players) {

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
        while (m_players.isEmpty()) {
            pollMessagesWait();
            if (m_players.size() == 1)
                std::cout << "[Serv][WaitP] \tFirst connection, start chrono" << std::endl;
            else
                std::cout << "[Serv][WaitP] \t Warning, expect new client" << std::endl;
        }

        sf::Clock clockWaitPlayers;

        while (clockWaitPlayers.getElapsedTime() < timeoutWaitPlayers) {
            if (m_players.size() == 0)
                break;
            pollMessagesWait(timeoutWaitPlayers - clockWaitPlayers.getElapsedTime());
        }
    } while (m_players.size() == 0);
}

void Server::createGame() {
    std::cout << "[Create] \tGame" << std::endl;
    // @TODO : switch with different game type
    m_game = new ServerGameSpeedestWin(*this, m_players, MapHeader(200, 200, 42));
}

void Server::sendGame() {
    std::cout << "[Broad] \tGame" << std::endl;
    sf::Packet packet;
    MsgGame msgGame;
//    m_game->toPacket(packet);
    msgGame << sf::Int32(200) << sf::Int32(200) << sf::Int32(42) << sf::Int32(42);
    //    packet >> msgGame;// @TODO

    m_network.getTCPManager().send(msgGame, m_players.inGame());
    waitAcknowledgment(m_players.inGame().size());
}

void Server::startGame() {
    m_game->start();
}

bool Server::pollMessagesWait(sf::Time timeout) {
    std::cout << "[Serv][PollM][Start] \t Poll messages started (With wait)" << std::endl;
    if (m_network.getMessageQueue().empty())
        if (!m_network.getMessageQueue().waitEvent(timeout)) {
            std::cout << "[Serv][PollM][End] \t Poll messages ended (With timeout)" << std::endl;
            return false;

        }
    pollMessages();
    std::cout << "[Serv][PollM][End] \t Poll messages ended (With receive message)" << std::endl;
    return true;
}

void Server::pollMessages() {
    //    std::cout << "[Serv][PollM][Start] \t Poll messages started" << std::endl;
    while (!m_network.getMessageQueue().empty()) {
        auto pair = m_network.getMessageQueue().pop();
        read(pair.second, pair.first);
    }
    //    std::cout << "[Serv][PollM][End] \t Poll messages ended" << std::endl;
}

bool Server::read(MessageData* message, ServerPlayer * player) {
    std::cout << "[Serv][Read][Start] \t Read message from " << player->getName() << std::endl;
    switch (message->getMsgType()) {
        case MsgType::ClientPlayerInfo:
        {
            std::cout << "[Serv][Read] \t Read ClientPlayerInfo" << std::endl;
            auto msgCPI = static_cast<MsgClientPlayerInfo> (*message);
            // Receive info from Client
//            std::cout << "[Serv][Read] \t cast done : " << msgCPI << std::endl;
            player->setUdpPort(msgCPI.getPort());
            std::cout << "[Serv][Read] \t getPort done" << std::endl;
            std::string name = msgCPI.getName();
            std::cout << "[Serv][Read] \t getName done" << std::endl;
            player->setName(name);
            std::cout << "[Serv][Read] \t Read info client : " << player->getName() << ":" << player->getUdpPort() << std::endl;
            // Send info to Client
            MsgServerPlayerInfo msgServer(42, SERVER_PORT_UDP); // @TODO
            m_network.getTCPManager().send(msgServer, player->getTCPSocket());
        }
            break;
        case MsgType::Acknowledgment:
        {
            std::cout << "Ack" << std::endl;
            m_acknowledgment.release();
        }
            break;
        case MsgType::Undef:
        {
            std::cout << "Undefined" << std::endl;
            return false;
        }
            break;
        default:
            std::cout << "[Serv][Read][Err] \t Server can't read this message" << std::endl;
            if (m_game == nullptr)
                return false;

            return m_game->read(message, player);
    }
    return true;
}

void Server::waitAcknowledgment(int permits) {
    m_acknowledgment.aquire(permits);
}
