/* 
 * File:   ServerWorld.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 15:19
 */

#include <iostream>

#include "shared/Utils.h"
#include "server/ServerWorld.h"
#include "server/serverCheckpoint/ServerCheckpointManager.h"

ServerWorld::ServerWorld() {
}

ServerWorld::~ServerWorld() {
    delete m_map;
}

void ServerWorld::initialize() {
    m_map = new HeigthMap(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
    std::cout << "map created" << std::endl;
    /*m_checkpointManager.initialise(m_map);
    std::cout << "checkpoints created" << std::endl;*/
    

}

void ServerWorld::update(float dt) {
    //recv
    //...
    //send
}

sf::Packet ServerWorld::getMapPacket(void) const {
    sf::Packet packet;
    packet << m_map->getWidth() << m_map->getHeight() << m_map->getSeed();
    
    return packet;
}