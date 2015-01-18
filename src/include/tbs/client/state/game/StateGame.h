/* 
 * File:   StateGame.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef STATEGAME_H
#define	STATEGAME_H

#include "client/state/State.h"
#include "client/state/game/GameStateManager.h"

class ClientState;
class ClientNetwork;
class ClientPlayer;

class StateGame : public State {
public:
    explicit StateGame(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~StateGame(void);

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);
    
private:
    GameStateManager m_states;
};

#endif	/* STATEGAME_H */

