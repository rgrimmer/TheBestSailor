/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>
#include <unistd.h>
#include <vector>
#include <ctime>
#include <thread>

#include <SFML/System/Time.hpp>

#include "shared/Utils.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MsgClientPlayerInfo.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/MessageData.h"

#include "server/game/ServerGame.h"
#include "server/game/ServerGameSpeedestWin.h"
#include "server/network/ServerMessageQueue.h"

#include "server/Server.h"
#include "shared/network/UtilsNetwork.h"

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
    sf::Time timeoutWaitPlayers = sf::milliseconds(20000);

    // Main loop, game can't start without player
    do {
        // Wait first player
        while (m_players.isEmpty()) {
            pollMessagesWait();
            if (m_players.size() == 1)
                std::cout << "[NetW] \tFirst connection, start chrono";
            else
                std::cout << "[NetW] \t Warning, expect new client";
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
    m_game->toPacket(packet);
//    packet >> msgGame; @TODO

    m_network.getTCPManager().send(msgGame, m_players.inGame());
    waitAcknowledgment(m_players.inGame().size());
}

void Server::startGame() {
    m_game->start();
}

bool Server::pollMessagesWait(sf::Time timeout) {
    if (m_network.getMessageQueue().empty())
        if (!m_network.getMessageQueue().waitEvent(timeout))
            return false;
    pollMessages();
    return true;
}

void Server::pollMessages() {
    while (!m_network.getMessageQueue().empty()) {
        auto pair = m_network.getMessageQueue().pop();
        read(pair.second, pair.first);
    }
}

bool Server::read(MessageData* message, ServerPlayer * player) {
    switch (message->getType()) {
        case MsgType::MSG_CLIENT_PLAYER_INFO:
        {
            auto msg = dynamic_cast<MsgClientPlayerInfo*> (message);
            // Receive info from Client
            player->setName(msg->getName());
            player->setUdpPort(msg->getPort());

            // Send info to Client
            MsgServerPlayerInfo msgServer(42, SERVER_PORT_UDP); // @TODO
            m_network.getTCPManager().send(msgServer, player->getTCPSocket());
        }
            break;
        case MsgType::MSG_ACK:
        {
            std::cout << "Ack" << std::endl;
            m_acknowledgment.release();
        }
            break;
        default:
            if (m_game == nullptr)
                return false;

            return m_game->read(message, player);
    }
    return true;
}

void Server::waitAcknowledgment(int permits) {
    m_acknowledgment.aquire(permits);
}
