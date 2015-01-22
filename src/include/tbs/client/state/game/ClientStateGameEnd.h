/* 
 * File:   ClientStateGameEnd.h
 * Author: maxence
 *
 * Created on 22 janvier 2015, 20:10
 */

#ifndef CLIENTSTATEGAMEEND_H
#define	CLIENTSTATEGAMEEND_H

#include <SFML/System/Clock.hpp>

#include "client/state/game/ClientStateGameStarted.h"

class ClientStateGameEnd : public ClientStateGameStarted {
public:
    ClientStateGameEnd(ClientStateGame& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world);
    virtual ~ClientStateGameEnd();
    

    virtual void activate();
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;

private:
    sf::Clock m_timeLeft;

};

#endif	/* CLIENTSTATEGAMEEND_H */

