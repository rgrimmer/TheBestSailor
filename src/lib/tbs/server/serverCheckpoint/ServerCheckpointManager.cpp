/* 
 * File:   CheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#include "server/serverCheckpoint/ServerCheckpoint.h"


#include <vector>


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
        m_checkpoints.emplace_back(checkpointsPos[i]);
    }
}

void ServerCheckpointManager::release() {
    m_checkpoints.clear();
}

void ServerCheckpointManager::addCompletedCheckpoint(ServerPlayer* player, int indexCheckpoint) {
    m_completedCheckpoints[player].push_back(indexCheckpoint);
}

bool ServerCheckpointManager::isCompletedCheckpoint(ServerPlayer* player, int indexCheckpoint) {
    return std::find(m_completedCheckpoints[player].begin(), m_completedCheckpoints[player].end(), indexCheckpoint) != m_completedCheckpoints[player].end();
}

bool ServerCheckpointManager::isCompletedAllCheckpoint(ServerPlayer* player) const {
    const auto iterator = m_completedCheckpoints.find(player);
    if(iterator == m_completedCheckpoints.end()) {
        return false;
    }
    else {
        std::cout << player->getName() << " has " << (*iterator).second.size() << " checkpoints(" << getCheckPointCount()<<")"<< std::endl;
        return (*iterator).second.size() == getCheckPointCount();
    }
}

ServerCheckpoint& ServerCheckpointManager::getCheckPoint(int index) {
    return m_checkpoints.at(index);
}

unsigned int ServerCheckpointManager::getCheckPointCount() const {
    return m_checkpoints.size();
}

std::vector<ServerCheckpoint>& ServerCheckpointManager::getCheckPoints() {
    return m_checkpoints;
}
