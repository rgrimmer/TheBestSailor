/* 
 * File:   ServerPlayers.h
 * Author: maxence
 *
 * Created on 15 décembre 2014, 18:28
 */

#ifndef SERVERPLAYERS_H
#define	SERVERPLAYERS_H

#include <vector>

#include <SFML/Network/IpAddress.hpp>

#include "ServerPlayer.h"

class ServerPlayer;

class ServerPlayers {
public:
    ServerPlayers();
    virtual ~ServerPlayers();

    int size() const;
    bool isEmpty() const;
    
    ServerPlayer& addNewPlayer();
    ServerPlayer* getPlayer(sf::IpAddress senderAddress, unsigned short senderPort);
    void remove(ServerPlayer &player);
    
    const std::vector<ServerPlayer*>&  inGame() const;
    const std::vector<ServerPlayer*>&  inWait() const;
    std::vector<ServerPlayer*>& getList();
    
    void putPlayersInGame();

private:
    std::vector<ServerPlayer*> m_players;
    std::vector<ServerPlayer*> m_inWaitPlayers;
    std::vector<ServerPlayer*> m_inGamePlayers;

};

#endif	/* SERVERPLAYERS_H */

