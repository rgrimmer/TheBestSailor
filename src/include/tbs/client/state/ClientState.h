/* 
 * File:   ClientState.h
 * Author: maxence
 *
 * Created on 17 janvier 2015, 17:36
 */

#ifndef CLIENTSTATE_H
#define	CLIENTSTATE_H

#include "client/state/StateManager.h"
#include "client/state/EClientState.h"

class ClientState : public StateManager<EClientState> {
public:
    ClientState(ClientNetwork& network, ClientPlayer& player);
    virtual ~ClientState();

    virtual void initialize();



private:
    ClientNetwork& m_network;
    ClientPlayer& m_player;
};

#endif	/* CLIENTSTATE_H */

