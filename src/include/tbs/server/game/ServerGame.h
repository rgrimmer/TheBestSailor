/* 
 * File:   ServerGame.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:08
 */

#ifndef SERVERGAME_H
#define	SERVERGAME_H

#include <vector>

class MessageData;
class ServerPlayers;
class Server;
class ServerPlayer;

class ServerGame {
public:
    ServerGame(Server &server, ServerPlayers& players);
    virtual ~ServerGame();

    void start();

    virtual bool read(MessageData* message, ServerPlayer* player) = 0;
    virtual sf::Packet toPacket(sf::Packet& packet) const = 0;

protected:
    virtual void initGame() = 0;
    virtual void startGameLoop() = 0;
    
protected:
    Server &m_server;
    ServerPlayers& m_players;
};

#endif	/* SERVERGAME_H */

