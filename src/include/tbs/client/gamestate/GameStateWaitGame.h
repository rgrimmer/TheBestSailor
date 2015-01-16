/* 
 * File:   GameStateWaitGame.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef GAMESTATEWAITGAME_H
#define	GAMESTATEWAITGAME_H

#include "client/gamestate/GameState.h"

class GameStateWaitGame : public GameState {
public:
    GameStateWaitGame(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player);
    virtual ~GameStateWaitGame();
    

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

#endif	/* GAMESTATEWAITGAME_H */

