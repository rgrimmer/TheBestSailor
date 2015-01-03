/* 
 * File:   ServerCheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <vector>

#include "server/serverCheckpoint/ServerCheckpoint.h"

class HeigthMap;

class ServerCheckpointManager {
public:
    ServerCheckpointManager();
    virtual ~ServerCheckpointManager();

    void initialise(HeigthMap& map);
    void release(void);
    
    int getCheckPointCount();
    ServerCheckpoint& getCheckPoint(int index);
    std::vector<ServerCheckpoint>& getCheckPoints(void);

private:
    std::vector<ServerCheckpoint> m_checkpoints;

};