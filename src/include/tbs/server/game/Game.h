/* 
 * File:   Game.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:08
 */

#ifndef GAME_H
#define	GAME_H

#include <vector>

#include "server/ServerPlayer.h"

class Game {
public:
    Game(std::vector<ServerPlayer*> &waitingPlayers);
    virtual ~Game();

    const std::vector<ServerPlayer*> getPlayers() const;
    virtual void startGameLoop() = 0;

private:
    std::vector<ServerPlayer*> &m_waitingPlayers;
    std::vector<ServerPlayer*> m_listPlayers;

};

#endif	/* GAME_H */

