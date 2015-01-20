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

class ClientState;
class ClientNetwork;
class ClientPlayer;

enum EStateGame {
    Wait,
    Started
};

class ClientStateGame : public StateManager<EStateGame> {
public:
    explicit ClientStateGame(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~ClientStateGame(void);

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);
    
    
    ClientState& getManager();
    
private:
    ClientState& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    
    ClientWorld m_world;
};

#endif	/* STATEGAME_H */

