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
    m_inWaitPlayers.push_back(m_player);
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
    auto itInGame = std::find(m_inGamePlayers.begin(), m_inGamePlayers.end(), &playerToRemove);
    if (itInGame != m_inGamePlayers.end()) {
        std::cout << "Find in game " << &playerToRemove << " = " << *itInGame << " : " << (*itInGame)->getId() << " " << (*itInGame)->getName() << std::endl;
        m_inGamePlayers.erase(itInGame);
    } else {
        auto itInWait = std::find(m_inWaitPlayers.begin(), m_inWaitPlayers.end(), &playerToRemove);
        m_inWaitPlayers.erase(itInWait);
    }
    auto itPlayer = std::find(m_players.begin(), m_players.end(), &playerToRemove);
    std::cout << "Find player " << &playerToRemove << " = " << *itPlayer << " : " << (*itPlayer)->getId() << " " << (*itPlayer)->getName() << std::endl;
    delete *itPlayer;
    m_players.erase(itPlayer);
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


