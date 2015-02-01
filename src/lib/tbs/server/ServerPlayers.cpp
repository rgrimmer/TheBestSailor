/* 
 * File:   ServerPlayers.cpp
 * Author: maxence
 * 
 * Created on 15 décembre 2014, 18:28
 */
#include <iostream>

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"

std::atomic<unsigned int> ServerPlayers::s_nextId(1);

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
    m_players.emplace_back(new ServerPlayer());

    ServerPlayer *m_player = m_players[m_players.size() - 1];
    m_player->setId(ServerPlayers::s_nextId++);
    m_inWaitPlayers.insert(m_player);
    std::cout << "[Players] \t New player added" << std::endl;
    return *m_player;
}

ServerPlayer* ServerPlayers::getPlayer(sf::IpAddress senderAddress, unsigned short senderPort) {
    for (ServerPlayer* player : m_players) {
        if (player->getAddress() == senderAddress && player->getUdpPort() == senderPort)
            return player;
    }
    return nullptr;
}

std::vector<ServerPlayer*>& ServerPlayers::getList() {
    return m_players;
}

void ServerPlayers::remove(ServerPlayer& playerToRemove) {
    if (m_inGamePlayers.erase(&playerToRemove)) {
        std::cout << "Find in game " << std::endl;
    }
    if (m_inWaitPlayers.erase(&playerToRemove)) {
        std::cout << "Find in wait " << std::endl;
    }
    if (m_inConnectionPlayers.erase(&playerToRemove)) {
        std::cout << "Find in connection " << std::endl;
    }
    
    auto itPlayer = std::find(m_players.begin(), m_players.end(), &playerToRemove);
    std::cout << "Find player " << &playerToRemove << " = " << *itPlayer << " : " << (*itPlayer)->getId() << " " << (*itPlayer)->getName() << std::endl;
    delete *itPlayer;
    m_players.erase(itPlayer);
}

const std::unordered_set<ServerPlayer*>& ServerPlayers::inWait() const {
    return m_inWaitPlayers;
}

const std::unordered_set<ServerPlayer*>& ServerPlayers::inGame() const {
    return m_inGamePlayers;
}

const std::unordered_set<ServerPlayer*>& ServerPlayers::inConnection() const {
    return m_inConnectionPlayers;
}

void ServerPlayers::putPlayersInGameToInWait() {
    std::cout << "put players in game to in wait" << std::endl;
    m_inWaitPlayers.insert(m_inGamePlayers.begin(), m_inGamePlayers.end());
    m_inGamePlayers.clear();
}


void ServerPlayers::putPlayersInGame() {
    std::cout << "put players in game" << std::endl;
    m_inWaitPlayers.swap(m_inGamePlayers);
}

void ServerPlayers::setPlayerReady(ServerPlayer &player) {
    m_inConnectionPlayers.erase(&player);
    m_inWaitPlayers.insert(&player);
}


