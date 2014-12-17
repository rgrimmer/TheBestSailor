/* 
 * File:   PlayerList.h
 * Author: maxence
 *
 * Created on 15 décembre 2014, 18:28
 */

#ifndef PLAYERLIST_H
#define	PLAYERLIST_H

#include <vector>

#include <SFML/Network/IpAddress.hpp>

class ServerPlayer;

class PlayerList {
public:
    PlayerList();
    virtual ~PlayerList();

    int size() const;
    bool isEmpty() const;
    
    ServerPlayer& addNewPlayer();
    ServerPlayer* getPlayer(sf::IpAddress senderAddress, unsigned short senderPort);
    
    const std::vector<ServerPlayer*>&  inGame() const;
    const std::vector<ServerPlayer*>&  inWait() const;
    std::vector<ServerPlayer>& getList();
    
    void putPlayersInGame();

private:
    std::vector<ServerPlayer> m_players;
    std::vector<ServerPlayer*> m_inWaitPlayers;
    std::vector<ServerPlayer*> m_inGamePlayers;

};

#endif	/* PLAYERLIST_H */

