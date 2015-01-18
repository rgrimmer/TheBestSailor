/* 
 * File:   ServerCheckpointManager.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <vector>

#include "server/serverCheckpoint/ServerCheckpoint.h"
#include "server/ServerPlayer.h"

class HeigthMap;

class ServerCheckpointManager {
public:
    ServerCheckpointManager();
    virtual ~ServerCheckpointManager();

    void initialise(HeigthMap& map);
    void release(void);
    
    void addCompletedCheckpoint(ServerPlayer* player, int indexCheckpoint);
    bool isCompletedCheckpoint(ServerPlayer* player, int indexCheckpoint);
    bool isCompletedAllCheckpoint(ServerPlayer* player) const;
    
    unsigned int getCheckPointCount() const;
    ServerCheckpoint& getCheckPoint(int index);
    std::vector<ServerCheckpoint>& getCheckPoints(void);

private:
    std::vector<ServerCheckpoint> m_checkpoints;
    std::map<ServerPlayer*, std::vector<int>> m_completedCheckpoints;
};