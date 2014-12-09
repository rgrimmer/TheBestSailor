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

#include "shared/Utils.h"

Server::Server() {
}

Server::~Server() {

}

void Server::receive(ServerUDPManager& udpManager, SynchronizedQueue<sf::Packet>& inQueue) {
    std::cout << "receive thread started" << std::endl;
    while (true) {
        sf::Packet packet = udpManager.receive();
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

    m_tcpManager.initialize(SERVER_PORT_TCP);
    m_tcpManager.waitConnections(packet, m_players);

    m_udpManager.initialize(SERVER_PORT_UDP);

    //send player list to others
    sf::Packet playersList;

    playersList << static_cast<sf::Uint8> (m_players.size());

    for (ServerPlayer* p : m_players) {
        playersList << static_cast<sf::Uint8>(p->getId());
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
            
            sf::Packet packet;
            packet << 0;

            for (ServerPlayer* p : m_players) {
                std::cout << " sending resp to : " << p->getName() << " port = " << p->getUdpPort() << std::endl;
                m_udpManager.send(packet, p->getAddress(), p->getUdpPort());
            }
        }
    }

    for (ServerPlayer* p : m_players) {
        delete p;
    }

    m_players.empty();
}