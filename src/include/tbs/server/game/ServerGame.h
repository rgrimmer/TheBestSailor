/* 
 * File:   ServerGame.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:08
 */

#ifndef SERVERGAME_H
#define	SERVERGAME_H

#include <vector>

#include <SFML/System/Clock.hpp>

class MsgData;
class ServerPlayers;
class ServerPlayer;
class Server;

class ServerGame {
public:
    ServerGame(Server &server, ServerPlayers& players);
    virtual ~ServerGame();

    void start();

    void doUpdate();
    
    virtual void sendGame() = 0;
    virtual bool read(MsgData& message, ServerPlayer& player) = 0;
    virtual sf::Packet toPacket(sf::Packet& packet) const = 0;

protected:
    /* should not be called in herited classes*/
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void sendInfo() = 0;
    virtual bool gameIsEnded() = 0;

protected:
    Server &m_server;
    ServerPlayers& m_players;

private:
    sf::Clock m_updateClock;
};

#endif	/* SERVERGAME_H */

