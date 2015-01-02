/* 
 * File:   CheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#include "server/PathFinding.h"
#include "server/serverCheckpoint/ServerCheckpointManager.h"

#include "shared/Utils.h"

ServerCheckpointManager::ServerCheckpointManager()
: m_checkpoints() {

}

ServerCheckpointManager::~ServerCheckpointManager() {

}

void ServerCheckpointManager::initialise(Map *map) {
    PathFinding p;
    sf::Vector2i checkpointsPos[4];

    bool pathFound;
    bool restart = false;

    int attempts = 0;

    do {
        restart = false;
        p.loadMap(&map->getHeightMap());
        sf::Vector2i startPoint = p.choosePoint(PathFinding::area_center);

        for (int i = 0; i < 4; ++i) {

            attempts = 0;

            do {
                checkpointsPos[i] = p.choosePoint((PathFinding::area)(PathFinding::area_north_east + i));
                pathFound = p.find(startPoint, checkpointsPos[i]);
                attempts++;
            } while (!pathFound && attempts <= 1);

            if (!pathFound) {
                // new map
                std::cout << "No path found, changing map" << std::endl;
                delete map;
                map = new Map(MapHeader(NB_TILES_HEIGHT, NB_TILES_WIDTH, rand()));
                restart = true;
                break;
            }
        }

    } while (restart);
    
    for (int i = 0; i < 4; ++i) {
        ServerCheckpoint* c = new ServerCheckpoint(checkpointsPos[i]);
        m_checkpoints.push_back(c);
    }
}

void ServerCheckpointManager::release() {
    for (unsigned int i = 0; i < m_checkpoints.size(); ++i) {
        delete m_checkpoints.front();
    }

    m_checkpoints.clear();
}