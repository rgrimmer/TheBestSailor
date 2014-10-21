/* 
 * File:   CheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <list>

#include "shared/checkpoint/Checkpoint.h"
#include "shared/map/Map.h"

class CheckpointManager {
    
public:
    CheckpointManager();
    virtual ~CheckpointManager();
    
    void    release();
    void    addCheckpoint(Checkpoint* c);
    
private:
    std::list<Checkpoint*> m_checkpoints;

};