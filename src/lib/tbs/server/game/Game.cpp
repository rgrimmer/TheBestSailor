/* 
 * File:   Game.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:08
 */

#include "server/game/Game.h"

Game::Game(std::vector<ServerPlayer*>& waitingPlayers)
: m_waitingPlayers(waitingPlayers) {
    m_waitingPlayers.swap(m_listPlayers);
}

Game::~Game() {
}

const std::vector<ServerPlayer*> Game::getPlayers() const {
    return m_listPlayers;
}

