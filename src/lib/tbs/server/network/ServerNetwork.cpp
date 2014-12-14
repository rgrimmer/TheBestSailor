/* 
 * File:   ServerNetwork.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 13:32
 */

#include <iostream>

#include "shared/network/Request.h"
#include "shared/network/RequestTurnHelm.h"
#include "shared/network/RequestTurnSail.h"

#include "server/network/ServerNetwork.h"

ServerNetwork::ServerNetwork(Server& server)
: m_server(server) {

//    startUDPThread();
    m_udpManager.initialize(SERVER_PORT_UDP);
}

ServerNetwork::~ServerNetwork() {
}

void ServerNetwork::startTCPThread() {
    m_threadTCP = new std::thread(&ServerNetwork::tcpReceiveLoop, this);
}

void ServerNetwork::startUDPThread() {
    m_threadUDP = new std::thread(&ServerNetwork::udpReceiveLoop, this);
}

void ServerNetwork::tcpReceiveLoop() {
    while(true) {
    }
}
void ServerNetwork::udpReceiveLoop() {
    std::cout << "UDP Receive thread started" << std::endl;
    while (true) {
        sf::Packet packet = m_udpManager.receive();
        std::cout << "[recv]";
        if (packet.getDataSize() > 0) {
            m_inQueue.push(packet);
        }
    }
    std::cout << "UDP Receive thread ended" << std::endl;
}

void ServerNetwork::waitConnection() {
    m_tcpManager.waitConnections(SERVER_PORT_TCP , m_server.m_waitingPlayers);
}

void ServerNetwork::broadcastGame() {
    sf::Packet packetGame;
    packetGame << m_server.m_game;
    
    for (const auto &player : m_server.m_game->getPlayers()) {
        m_tcpManager.send(packetGame, player->getTCPSocket());
    }
}

void ServerNetwork::mainLoop() {
    //send player list to others
    sf::Packet playersList;

    playersList << static_cast<sf::Uint8> (m_server.m_game->getPlayers().size());

    for (const auto p : m_server.m_game->getPlayers()) {
        playersList << static_cast<sf::Uint8> (p->getId());
        playersList << p->getName();
    }

    std::cout << "send players list to all players.........." << std::endl;
    for (const auto p : m_server.m_game->getPlayers()) {
        m_tcpManager.send(playersList, p->getTCPSocket());
    }

    std::cout << "receiving udp port of all players.........." << std::endl;
    //receiving an ident msg from other players
    if (!m_udpManager.receiveIdentifyRequests(m_server.m_game->getPlayers())) {
        std::cout << "Error receive identify request" << std::endl;
        return;
    }
while (true) {

        //update

        if (!m_inQueue.empty()) {
            sf::Packet packetReceived = m_inQueue.pop();

            auto idPlayer = Request::popID(packetReceived);
            auto reqType = RequestData::popType(packetReceived);

            std::cout << "[read] from " << m_server.m_game->getPlayers().at(idPlayer)->getName() << " -> Action ";

            switch (reqType) {
                case REQ_ACTION_TURN_HELM:
                {
                    std::cout << "Turn Helm ";
                    RequestTurnHelm turnHelm;
                    turnHelm.fromPacketWithoutType(packetReceived);
                    //                    turnHelm << packetReceived;
                    if (turnHelm.getOrientation() == reqOrientation::POSITIVE)
                        std::cout << "POSITIVE";
                    else if (turnHelm.getOrientation() == reqOrientation::NEGATIVE)
                        std::cout << "NEGATIVE";
                    else
                        std::cout << "UNDEFINED (WARNING)";
                }
                    break;
                case REQ_ACTION_TURN_SAIL:
                {
                    std::cout << "Turn Sail ";
                    RequestTurnSail turnSail;
                    turnSail.fromPacketWithoutType(packetReceived);
                    //                    turnSail << packetReceived;
                    if (turnSail.getOrientation() == reqOrientation::POSITIVE)
                        std::cout << "POSITIVE";
                    else if (turnSail.getOrientation() == reqOrientation::NEGATIVE)
                        std::cout << "NEGATIVE";
                    else
                        std::cout << "UNDEFINED (WARNING)";
                }
                    break;
                case REQ_DISCONNECT:
                {
                    std::cout << "TODO : Disconnect";
//                    m_players.erase(m_players.begin() + idPlayer);
                }
                    break;
                default:
                    std::cout << "UNDEFINED (WARNING)";

                    break;

            }
            std::cout << std::endl;

            sf::Packet packetResponse;
            packetResponse << 0;

            for (ServerPlayer* p : m_server.m_game->getPlayers()) {
                std::cout << "[send] resp to : " << p->getName() << " port = " << p->getUdpPort() << std::endl;
                m_udpManager.send(packetResponse, p->getAddress(), p->getUdpPort());
            }
        }
    }

//    for (ServerPlayer* p : m_players) {
//        delete p;
//    }
//
//    m_players.empty();
}
