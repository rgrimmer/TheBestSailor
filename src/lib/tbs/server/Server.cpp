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
    m_serverNetwork = new ServerNetwork(*this);
}

Server::~Server() {
    delete m_serverNetwork;
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
    m_serverNetwork->initialize();
}

void Server::startChronoAndWait() {
    // @TODO : Dynamic chrono. Can be reset
//    sleep(15);
    m_serverNetwork->waitConnection();
}

void Server::createGame() {
    std::cout << "[Create] \tGame" << std::endl;
    // @TODO : switch with different game type
    m_game = new GameSpeedestWin(m_waitingPlayers, MapHeader(200, 200, 42));
}

void Server::sendGame() {
    std::cout << "[Broad] \tGame" << std::endl;
    m_serverNetwork->broadcastGame();
}

void Server::startGame() {
    std::cout << "[Start] \tMain Loop" << std::endl;
    m_serverNetwork->mainLoop();
    //    m_game->startGameLoop();
}

//void Server::receiveTCP() {
//    std::cout << "receiveTCP thread started" << std::endl;
//    while (true) {
//        sf::Packet packet = udpManager.receive();
//        std::cout << "[recv]";
//        if (packet.getDataSize() > 0) {
//            inQueue.push(packet);
//        }
//    }
//    std::cout << "receiveTCP thread ended" << std::endl;
//}

//    
//    m_map = new HeigthMap(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
//    std::cout << "map created" << std::endl;
//
//    sf::Packet packet;
//    packet << m_map->getWidth() << m_map->getHeight() << m_map->getSeed();
//
//    m_tcpManager.waitConnections(SERVER_PORT_TCP, packet, m_players);
//
//    m_udpManager.initialize(SERVER_PORT_UDP);
//
//    //send player list to others
//    sf::Packet playersList;
//
//    playersList << static_cast<sf::Uint8> (m_players.size());
//
//    for (ServerPlayer* p : m_players) {
//        playersList << static_cast<sf::Uint8> (p->getId());
//        playersList << p->getName();
//    }
//
//    std::cout << "send players list to all players.........." << std::endl;
//    for (ServerPlayer* p : m_players) {
//        m_tcpManager.send(playersList, p->getTCPSocket());
//    }
//
//    std::cout << "receiving udp port of all players.........." << std::endl;
//    //receiving an ident msg from other players
//    if (!m_udpManager.receiveIdentifyRequests(m_players)) {
//        std::cout << "Error receive identify request" << std::endl;
//        return;
//    }
//
//
//    std::thread receiver(&receive, std::ref(m_udpManager), std::ref(m_inQueue));
//
//    
//}