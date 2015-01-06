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
    std::cout << "[Players][Start] \t Add new player started" << std::endl;
    m_players.push_back(new ServerPlayer());
    std::cout << "player list : " << std::endl;
    for (const auto& p : m_players)
        std::cout << p << " " << p->getName() << std::endl;

    ServerPlayer *m_player = m_players[m_players.size() - 1];
    m_player->setId(ServerPlayers::s_nextId++);
    m_inWaitPlayers.insert(m_player);
    std::cout << "[Players][End] \t Add new player done" << std::endl;
    return *m_player;
}

ServerPlayer* ServerPlayers::getPlayer(sf::IpAddress senderAddress, unsigned short senderPort) {
    //    std::cout << "search ("<< senderAddress.toString() << ":" << senderPort << ")"<< std::endl;
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

void ServerPlayers::putPlayersInGame() {
    m_inWaitPlayers.swap(m_inGamePlayers);
}

void ServerPlayers::setPlayerReady(ServerPlayer &player) {
    m_inConnectionPlayers.erase(&player);
    m_inWaitPlayers.insert(&player);
}


