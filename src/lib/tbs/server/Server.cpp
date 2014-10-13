/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include "server/Server.h"

#include <iostream>


sf::Packet& operator<< (sf::Packet &packet, const Map &map) {
    int mapSize = map.size();

    // @TODO check syntaxe of cast
    packet << (sf::Int32) map.width() << (sf::Int32) map.height();
    
    for (int i = 0; i < mapSize; ++i)
        packet << map[i];

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
    /*sf::UdpSocket socket;
    sf::IpAddress client = "localhost";
    unsigned short portClient = 1234, portServer = 54000;
    sf::Packet packet;*/
    
    m_connectionManager.bind(ConnectionManager::serverPort);

    // @TODO get a connection
    m_connectionManager.addRemote("localhost", ConnectionManager::clientPort);
    //std::cout << socket.receive(packet, client, portClient) << " ";
    //std::cout << "Connection receive : " << client << " " << portClient <<std::endl;
    
    // @TODO generate a map
    m_map = new Map();

    m_map->generate(800, 600);
    std::cout << "Map generate" << std::endl;


    // @TODO send map to client
    sf::Packet mapPacket;
    mapPacket << (*m_map);
    std::cout << "packet create" << mapPacket.getDataSize() <<std::endl;
    
    m_connectionManager.send(mapPacket);
    
    /*if (socket.send(mapPacket, client, portClient) != sf::Socket::Done) {
        std::cout << "Send error" << std::endl;

    }
    else
        std::cout << "Message send" << std::endl;*/
}