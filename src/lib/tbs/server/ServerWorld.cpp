/* 
 * File:   ServerWorld.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 15:19
 */

#include <SFML/Graphics/Drawable.hpp>

#include "shared/Utils.h"
#include "server/ServerWorld.h"
#include "server/serverCheckpoint/ServerCheckpointManager.h"

ServerWorld::ServerWorld() {
}

ServerWorld::~ServerWorld() {
    delete m_map;
}

void ServerWorld::initialize(void) {
    m_map = new HeigthMap(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));  
    m_checkpointManager.initialise(m_map);
}

void ServerWorld::update(float dt) {
    
}