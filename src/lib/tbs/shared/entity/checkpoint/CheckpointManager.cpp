/* 
 * File:   CheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#include "shared/entity/checkpoint/CheckpointManager.h"
#include "server/PathFinding.h"

CheckpointManager::CheckpointManager()
: m_checkpoints() {

}

CheckpointManager::~CheckpointManager() {

}

void CheckpointManager::release() {
    for (unsigned int i = 0; i < m_checkpoints.size(); ++i) {
        delete m_checkpoints.front();
    }

    m_checkpoints.clear();
}

void CheckpointManager::addCheckpoint(Checkpoint* c) {
    m_checkpoints.push_back(c);
}