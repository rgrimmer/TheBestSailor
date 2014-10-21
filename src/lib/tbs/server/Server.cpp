/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>

#include "server/Server.h"

#include "server/PathFinding.h"
#include "shared/checkpoint/Checkpoint.h"
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

void Server::start(void) {
    std::cout << "server start" << std::endl;
    m_connectionManager.bind(UdpSocketManager::serverPort);

    // @TODO get a connection
    m_connectionManager.addRemote("localhost", UdpSocketManager::clientPort);
    //std::cout << socket.receive(packet, client, portClient) << " ";
    //std::cout << "Connection receive : " << client << " " << portClient <<std::endl;

    // @TODO generate a map
    m_map = new Map(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
    std::cout << "Map generate" << std::endl;

    createCheckpoints();
    std::cout << "checkpoints create" << std::endl;
    
    // @TODO send map to client
    sf::Packet mapPacket;
    mapPacket << m_map->getHeader();
    std::cout << "packet create" << mapPacket.getDataSize() << std::endl;

    m_connectionManager.send(mapPacket);
}

//TODO remove non constants values
void Server::createCheckpoints() {
    PathFinding p;
    sf::Vector2i checkpointsPos[4];

    bool pathFound;
    bool restart = false;

    int attempts = 0;

    do {

        p.initialize(m_map);
        sf::Vector2i startPoint = p.choosePoint(PathFinding::area_center);

        for (int i = 0; i < 4; ++i) {

            attempts = 0;

            do {
                checkpointsPos[i] = p.choosePoint((PathFinding::area)(PathFinding::area_north_east + i));
                pathFound = p.find(startPoint, checkpointsPos[i]);
                attempts++;
            } while (!pathFound && attempts <= 100);

            if (!pathFound) {
                // new map
                delete m_map;
                m_map = new Map(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
                restart = true;
                break;
            }
        }

    } while (restart);

    for (int i = 0; i < 4; ++i) {
        Checkpoint* c = new Checkpoint(checkpointsPos[i]);
        m_checkpointManager.addCheckpoint(c);
    }
}