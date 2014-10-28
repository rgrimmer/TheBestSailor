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

void ServerCheckpointManager::initialise(HeigthMap *m_map) {
    PathFinding p;
    sf::Vector2i checkpointsPos[4];

    bool pathFound;
    bool restart = false;

    int attempts = 0;

    do {

        p.loadMap(m_map);
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
                m_map = new HeigthMap(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));
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