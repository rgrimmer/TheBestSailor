/* 
 * File:   GameSpeedestWin.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:19
 */

#ifndef GAMESPEEDESTWIN_H
#define	GAMESPEEDESTWIN_H

#include "Game.h"

#include <SFML/Network/Packet.hpp>

#include "shared/map/Map.h"

class GameSpeedestWin : public Game {
public:
    GameSpeedestWin(std::vector<ServerPlayer*> &waitingPlayers, const MapHeader &header);
    virtual ~GameSpeedestWin();

    const Map& getMap() const;
    virtual void startGameLoop();

private:
    Map m_map;
};

sf::Packet& operator<<(sf::Packet& packet, const GameSpeedestWin& game);

#endif	/* GAMESPEEDESTWIN_H */

