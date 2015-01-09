/* 
 * File:   CheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#include "shared/Utils.h"
#include "shared/map/HeigthMap.h"
#include "server/PathFinding.h"
#include "server/serverCheckpoint/ServerCheckpointManager.h"

ServerCheckpointManager::ServerCheckpointManager()
: m_checkpoints() {

}

ServerCheckpointManager::~ServerCheckpointManager() {

}

void ServerCheckpointManager::initialise(HeigthMap& map) {
    PathFinding p;
    sf::Vector2i checkpointsPos[4];

    bool pathFound;
    bool restart = false;

    int attempts = 0;

    do {
        restart = false;
        std::cout << "Map Address : " << &map << std::endl;
        p.loadMap(&map);
        sf::Vector2i startPoint = p.choosePoint(PathFinding::area_center);

        for (int i = 0; i < 4; ++i) {

            attempts = 0;

            do {
                checkpointsPos[i] = p.choosePoint((PathFinding::area)(PathFinding::area_north_east + i));
                pathFound = p.find(startPoint, checkpointsPos[i]);
                attempts++;
            } while (!pathFound && attempts <= 1);

            if (!pathFound) {
                map = HeigthMap(MapHeader(map.getHeight(), map.getWidth(), rand()));
                restart = true;
                break;
            }
        }

    } while (restart);

    for (int i = 0; i < 4; ++i) {
        m_checkpoints.push_back(ServerCheckpoint(sf::Vector2i(checkpointsPos[i].x*TILE_SIZE, checkpointsPos[i].y*TILE_SIZE)));
    }
}

void ServerCheckpointManager::release() {
    m_checkpoints.clear();
}

ServerCheckpoint& ServerCheckpointManager::getCheckPoint(int index) {
    return m_checkpoints.at(index);
}

int ServerCheckpointManager::getCheckPointCount() {
    return m_checkpoints.size();
}

std::vector<ServerCheckpoint>& ServerCheckpointManager::getCheckPoints() {
    return m_checkpoints;
}
