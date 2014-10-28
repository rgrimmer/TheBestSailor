/* 
 * File:   ServerWorld.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 15:19
 */

#ifndef SERVER_WORLD_H
#define	SERVER_WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "server/serverCheckpoint/ServerCheckpointManager.h"
#include "shared/map/HeigthMap.h"

class ServerWorld {
public:
    ServerWorld();
    virtual ~ServerWorld();

    void initialize(void);
    void update(float dt);

private:
    HeigthMap *m_map;
    ServerCheckpointManager m_checkpointManager;
};

#endif	/* SERVER_WORLD_H */

