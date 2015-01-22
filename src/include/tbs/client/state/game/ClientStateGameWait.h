/* 
 * File:   StateGameWait.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef CLIENTSTATEGAMEWAIT_H
#define	CLIENTSTATEGAMEWAIT_H

#include "client/state/State.h"
#include "client/view/menu/GameWaitView.h"

class ClientStateGame;
class ClientNetwork;
class ClientPlayer;
class ClientWorld;

class ClientStateGameWait : public State {
public:
    ClientStateGameWait(ClientStateGame& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world);
    virtual ~ClientStateGameWait();

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
    bool readTimeLeft(MsgData& msg);

private:
    ClientStateGame& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    ClientWorld& m_world;
    GameWaitView m_view;
};

#endif	/* StateGameWait_H */

