/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>
#include <unistd.h>

#include "server/Server.h"

#include "server/PathFinding.h"
#include "shared/entity/checkpoint/Checkpoint.h"
#include "shared/entity/map/MapHeader.h"
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
    m_map = new Map(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
    std::cout << "Map generate" << std::endl;

    createCheckpoints();
    std::cout << "checkpoints create" << std::endl;
    
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
//    m_clientManager.send(mapPacket);
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
            std::cout << "test" << std::endl;
            do {
            std::cout << "while choose" << std::endl;
                checkpointsPos[i] = p.choosePoint((PathFinding::area)(PathFinding::area_north_east + i));
            std::cout << "while find" << std::endl;
                pathFound = p.find(startPoint, checkpointsPos[i]);
                attempts++;
            std::cout << "while end" << std::endl;
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
