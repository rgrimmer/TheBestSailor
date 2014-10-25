/* 
 * File:   PlayerManager.cpp
 * Author: maxence
 * 
 * Created on 20 octobre 2014, 18:27
 */

#include "server/player/PlayerManager.h"

PlayerManager::PlayerManager() {
}

PlayerManager::PlayerManager(const PlayerManager& orig) {
}

PlayerManager::~PlayerManager() {
    for(unsigned int i = 0; i < m_players.size(); ++i)
        delete m_players[i];
}

void PlayerManager::addPlayer(const Player& player) {
    m_players.push_back(new Player(player));
}


void PlayerManager::addPlayer(Player* player) {
    m_players.push_back(player);
}