/* 
 * File:   ServerCheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <list>

#include "server/serverCheckpoint/ServerCheckpoint.h"
#include "shared/map/Map.h"

class ServerCheckpointManager {
public:
    ServerCheckpointManager();
    virtual ~ServerCheckpointManager();

    void initialise(Map* map);
    void release(void);
    
    int getCheckPointCount();
    ServerCheckpoint* getCheckPoint(int index);

private:
    std::vector<ServerCheckpoint*> m_checkpoints;

};