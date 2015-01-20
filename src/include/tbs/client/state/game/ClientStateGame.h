/* 
 * File:   StateGame.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef CLIENTSTATEGAME_H
#define	CLIENTSTATEGAME_H

#include "client/ClientWorld.h"

#include "client/state/StateManager.h"
#include "client/state/game/EClientStateGame.h"

class ClientState;
class ClientNetwork;
class ClientPlayer;

class ClientStateGame : public StateManager<EStateGame> {
public:
    explicit ClientStateGame(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~ClientStateGame(void);

    virtual void initialize(void);
    ClientState& getManager();
    
private:
    ClientState& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    
    ClientWorld m_world;
};

#endif	/* STATEGAME_H */

