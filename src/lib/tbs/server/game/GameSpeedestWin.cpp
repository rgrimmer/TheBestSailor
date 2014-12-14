/* 
 * File:   GameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:19
 */

#include "server/game/GameSpeedestWin.h"

sf::Packet& operator<<(sf::Packet& packet, const GameSpeedestWin& game) {
    return packet << game.getMap();
}

GameSpeedestWin::GameSpeedestWin(std::vector<ServerPlayer*>& waitingPlayers, const MapHeader &header) 
: Game(waitingPlayers)
, m_map(header) {
    
}

GameSpeedestWin::~GameSpeedestWin() {
}

const Map& GameSpeedestWin::getMap() const {
    return m_map;
}

void GameSpeedestWin::startGameLoop() {

}
