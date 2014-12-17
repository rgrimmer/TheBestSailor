/* 
 * File:   PlayerList.cpp
 * Author: maxence
 * 
 * Created on 15 décembre 2014, 18:28
 */

#include "server/PlayerList.h"
#include "server/ServerPlayer.h"

PlayerList::PlayerList() {
}

PlayerList::~PlayerList() {
}

bool PlayerList::isEmpty() const {
    return m_players.empty();
}

int PlayerList::size() const {
    return m_players.size();
}

ServerPlayer& PlayerList::addNewPlayer() {
    m_players.push_back(ServerPlayer());
    m_inWaitPlayers.push_back(&(m_players[m_players.size() - 1]));
    return m_players[m_players.size()-1];
}

ServerPlayer* PlayerList::getPlayer(sf::IpAddress senderAddress, unsigned short senderPort) {
    for(ServerPlayer& player : m_players) {
        if(player.getAddress() == senderAddress && player.getUdpPort() == senderPort)
            return &player;
    }
    return nullptr;
}

std::vector<ServerPlayer>& PlayerList::getList() {
    return m_players;
}

const std::vector<ServerPlayer*>& PlayerList::inWait() const {
    return m_inWaitPlayers;
}

const std::vector<ServerPlayer*>& PlayerList::inGame() const {
    return m_inGamePlayers;
}


void PlayerList::putPlayersInGame() {
    m_inWaitPlayers.swap(m_inGamePlayers);
}


