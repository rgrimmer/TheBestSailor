/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>

#include "server/Server.h"
#include "shared/Utils.h"

sf::Packet& operator<<(sf::Packet &packet, const Map &map) {
    int mapWidth = map.getWidth();
    int mapHeight = map.getHeight();

    // @TODO check syntaxe of cast
    packet << (sf::Int32) mapWidth << (sf::Int32) mapHeight;

    for (int i = 0; i < mapWidth; ++i) {
        for (int j = 0; j < mapHeight; ++j) {
            packet << map(i,j);
        }
    }

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

void Server::start(void) {
    std::cout << "server start" << std::endl;
    m_connectionManager.bind(UdpSocketManager::serverPort);

    // @TODO get a connection
    m_connectionManager.addRemote("localhost", UdpSocketManager::clientPort);
    //std::cout << socket.receive(packet, client, portClient) << " ";
    //std::cout << "Connection receive : " << client << " " << portClient <<std::endl;

    // @TODO generate a map
    int seed = rand();
    m_map = new Map(NB_TILES_WIDTH, NB_TILES_HEIGHT, seed);
    std::cout << "Map generate" << std::endl;


    // @TODO send map to client
    sf::Packet mapPacket;
    mapPacket << (*m_map);
    std::cout << "packet create" << mapPacket.getDataSize() << std::endl;

    m_connectionManager.send(mapPacket);
}