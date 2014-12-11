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

#include "server/Server.h"

#include "shared/network/Request.h"
#include "shared/network/RequestTurnHelm.h"

#include "shared/Utils.h"
#include "shared/network/RequestTurnSail.h"

Server::Server() {
}

Server::~Server() {

}

void Server::receive(ServerUDPManager& udpManager, SynchronizedQueue<sf::Packet>& inQueue) {
    std::cout << "receive thread started" << std::endl;
    while (true) {
        sf::Packet packet = udpManager.receive();
            std::cout << "[recv]";
        if (packet.getDataSize() > 0) {
            inQueue.push(packet);
        }
    }
    std::cout << "receive thread ended" << std::endl;
}

void Server::start() {
    srand(time(NULL));

    m_map = new HeigthMap(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
    std::cout << "map created" << std::endl;

    sf::Packet packet;
    packet << m_map->getWidth() << m_map->getHeight() << m_map->getSeed();

    m_tcpManager.waitConnections(SERVER_PORT_TCP, packet, m_players);

    m_udpManager.initialize(SERVER_PORT_UDP);

    //send player list to others
    sf::Packet playersList;

    playersList << static_cast<sf::Uint8> (m_players.size());

    for (ServerPlayer* p : m_players) {
        playersList << static_cast<sf::Uint8> (p->getId());
        playersList << p->getName();
    }

    std::cout << "send players list to all players.........." << std::endl;
    for (ServerPlayer* p : m_players) {
        m_tcpManager.send(playersList, p->getTCPSocket());
    }

    std::cout << "receiving udp port of all players.........." << std::endl;
    //receiving an ident msg from other players
    if (!m_udpManager.receiveIdentifyRequests(m_players)) {
        std::cout << "Error receive identify request" << std::endl;
        return;
    }


    std::thread receiver(&receive, std::ref(m_udpManager), std::ref(m_inQueue));

    while (true) {

        //update

        if (!m_inQueue.empty()) {
            sf::Packet packetReceived = m_inQueue.pop();

            auto idPlayer = Request::popID(packetReceived);
            auto reqType = RequestData::popType(packetReceived);

            std::cout << "[read] from " << m_players.at(idPlayer)->getName() << " -> Action ";

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
                    std::cout << "Disconnect";
                    m_players.erase(m_players.begin() + idPlayer);
                }
                    break;
                default:
                    std::cout << "UNDEFINED (WARNING)";

                    break;

            }
            std::cout << std::endl;

            sf::Packet packetResponse;
            packetResponse << 0;

            for (ServerPlayer* p : m_players) {
                std::cout << "[send] resp to : " << p->getName() << " port = " << p->getUdpPort() << std::endl;
                m_udpManager.send(packetResponse, p->getAddress(), p->getUdpPort());
            }
        }
    }

    for (ServerPlayer* p : m_players) {
        delete p;
    }

    m_players.empty();
}