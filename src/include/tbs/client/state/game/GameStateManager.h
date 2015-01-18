/* 
 * File:   GameStateManager.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 17:18
 */

#ifndef GAMESTATEMANAGER_H
#define	GAMESTATEMANAGER_H

#include "client/ClientWorld.h"

#include "client/state/StateManager.h"

enum EGameStateManager {
    Wait,
    Started
};

class ClientState;
class ClientNetwork;
class ClientPlayer;

class GameStateManager : public StateManager<EGameStateManager> {
public:
    GameStateManager(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~GameStateManager();

    ClientState& getManager();

    virtual void initialize();

private:
    ClientState& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    
    ClientWorld m_world;
};
#endif	/* GAMESTATEMANAGER_H */

