/* 
 * File:   StateWaitGame.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef STATEWAITGAME_H
#define	STATEWAITGAME_H

#include "client/state/State.h"

class ClientNetwork;
class ClientPlayer;

class StateWaitGame : public State {
public:
    StateWaitGame(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player);
    virtual ~StateWaitGame();
    

    virtual void Initialize();
    virtual void Release();

    virtual void Activate();
    virtual void DeActivate();

    virtual void Update(float dt);
    virtual void Render(sf::RenderWindow& window);

    virtual bool read(MsgData& msg);
    virtual bool read(sf::Event& msg);


private:

};

#endif	/* StateWAITGAME_H */

