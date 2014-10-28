/* 
 * File:   ServerCheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <list>

#include "server/serverCheckpoint/ServerCheckpoint.h"
#include "shared/map/HeigthMap.h"

class ServerCheckpointManager {
public:
    ServerCheckpointManager();
    virtual ~ServerCheckpointManager();

    void initialise(HeigthMap* m_map);
    void release(void);

private:
    std::list<ServerCheckpoint*> m_checkpoints;

};