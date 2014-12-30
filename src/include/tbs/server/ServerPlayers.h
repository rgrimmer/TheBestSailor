/* 
 * File:   ServerPlayers.h
 * Author: maxence
 *
 * Created on 15 décembre 2014, 18:28
 */

#ifndef SERVERPLAYERS_H
#define	SERVERPLAYERS_H
#include <atomic>
#include <vector>
#include <unordered_set>

#include <SFML/Network/IpAddress.hpp>

class ServerPlayer;

class ServerPlayers {
private:
    static std::atomic<unsigned int> s_nextId;

public:
    ServerPlayers();
    virtual ~ServerPlayers();

    int size() const;
    bool isEmpty() const;

    ServerPlayer& addNewPlayer();
    ServerPlayer* getPlayer(sf::IpAddress senderAddress, unsigned short senderPort);
    void remove(ServerPlayer &player);

    const std::unordered_set<ServerPlayer*>& inGame() const;
    const std::unordered_set<ServerPlayer*>& inWait() const;
    const std::unordered_set<ServerPlayer*>& inConnection() const;
    std::vector<ServerPlayer*>& getList();

    void setPlayerReady(ServerPlayer &player);
    void putPlayersInGame();

private:
    std::vector<ServerPlayer*> m_players;
    std::unordered_set<ServerPlayer*> m_inConnectionPlayers;
    std::unordered_set<ServerPlayer*> m_inWaitPlayers;
    std::unordered_set<ServerPlayer*> m_inGamePlayers;

};

#endif	/* SERVERPLAYERS_H */

