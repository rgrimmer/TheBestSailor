/* 
 * File:   ServerPlayers.cpp
 * Author: maxence
 * 
 * Created on 15 décembre 2014, 18:28
 */
#include <iostream>

#include "server/ServerPlayers.h"
#include "server/ServerPlayer.h"

ServerPlayers::ServerPlayers() {
}

ServerPlayers::~ServerPlayers() {
}

bool ServerPlayers::isEmpty() const {
    return m_players.empty();
}

int ServerPlayers::size() const {
    return m_players.size();
}

ServerPlayer& ServerPlayers::addNewPlayer() {
    std::cout << "[Players][Start] \t Add new player started" << std::endl;
    m_players.push_back(ServerPlayer());
    ServerPlayer &m_player = m_players[m_players.size() - 1];
    m_player.initialize();
    m_inWaitPlayers.push_back(&m_player);
    std::cout << "[Players][End] \t Add new player done" << std::endl;
    return m_player;
}

ServerPlayer* ServerPlayers::getPlayer(sf::IpAddress senderAddress, unsigned short senderPort) {
    for(ServerPlayer& player : m_players) {
        if(player.getAddress() == senderAddress && player.getUdpPort() == senderPort)
            return &player;
    }
    return nullptr;
}

std::vector<ServerPlayer>& ServerPlayers::getList() {
    return m_players;
}

void ServerPlayers::remove(ServerPlayer& playerToRemove) {
//    for(auto playerInList : m_inGamePlayers) {
//        if(&playerToRemove == playerInList) {
//            m_inGamePlayers.
//        }
//    } @TODO
}

const std::vector<ServerPlayer*>& ServerPlayers::inWait() const {
    return m_inWaitPlayers;
}

const std::vector<ServerPlayer*>& ServerPlayers::inGame() const {
    return m_inGamePlayers;
}

void ServerPlayers::putPlayersInGame() {
    m_inWaitPlayers.swap(m_inGamePlayers);
}


