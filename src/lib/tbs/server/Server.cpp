/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>
#include <unistd.h>

#include "server/Server.h"
#include "shared/map/MapHeader.h"
#include "shared/Utils.h"

sf::Packet& operator<<(sf::Packet &packet, const MapHeader &header) {
    int mapWidth = header.getWidth();
    int mapHeight = header.getHeight();
    int mapSeed = header.getSeed();

    // @TODO check syntaxe of cast
    packet << (sf::Int32) mapWidth
            << (sf::Int32) mapHeight
            << (sf::Int32) mapSeed
            ;
    return packet;
}

Server::Server() :
m_map(NULL) {
}

Server::Server(const Server& orig) {
}

Server::~Server() {
    delete m_map;
}

void Server::start() {
    std::cout << "server start" << std::endl;
    m_clientManager.setConnectionListener(this);

    // @TODO get a connection
    waitPlayers();
    //std::cout << socket.receive(packet, client, portClient) << " ";
    //std::cout << "Connection receive : " << client << " " << portClient <<std::endl;

    // @TODO generate a map
    int seed = rand();
    m_map = new Map(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, seed));
    std::cout << "Map generate " << m_map->getHeader().getHeight() << std::endl;


    // @TODO send map to client
    sf::Packet mapPacket;
    mapPacket << m_map->getHeader();

    m_clientManager.broadcastMessage(mapPacket);
    std::cout << "Map send" << std::endl;
    //m_clientManager.send(mapPacket);
}

void Server::waitPlayers() {
    addWaitingPlayers();
    m_clientManager.acceptPlayers(true);
    m_clientManager.startAsychroneReadLoop();
    // @TODO wait players are ready
    usleep(10000000);
    // Sleep
    m_clientManager.acceptPlayers(false);
}

void Server::addWaitingPlayers() {
    std::list<sf::Packet>& waitingPacket = m_clientManager.getWaitingClientPacket();
    std::list<SocketQueuBuffer*>& waitingBuffer = m_clientManager.getWaitingClientBuffer();

    // @TODO add players number limit
    int size = waitingPacket.size();
    for (int i = 0; i < size; ++i) {
        receiveConnection(*waitingPacket.begin(), *waitingBuffer.begin());
        waitingPacket.pop_front();
        waitingBuffer.pop_front();
    }
    //m_clientManager.addWaitingPlayers(m_players);
}

void Server::receiveConnection(sf::Packet& packet, SocketQueuBuffer* buffer) {
    std::cout << "Receive a connection !!" << std::endl;
    // @TODO move acceptConnection in Server

    std::string name;
    packet >> name;
    m_players.addPlayer(new Player(name, buffer));

    // @TODO send map

}