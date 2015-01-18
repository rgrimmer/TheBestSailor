/* 
 * File:   StateGameWait.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef STATEGAMEWAIT_H
#define	STATEGAMEWAIT_H

#include "client/state/State.h"

class GameStateManager;
class ClientNetwork;
class ClientPlayer;
class ClientWorld;

class StateGameWait : public State {
public:
    StateGameWait(GameStateManager& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world);
    virtual ~StateGameWait();

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    bool readInitGame(MsgData& msg);

private:
    GameStateManager& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    ClientWorld& m_world;
};

#endif	/* StateGameWait_H */

