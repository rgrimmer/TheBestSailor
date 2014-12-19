/* 
 * File:   ServerGameSpeedestWin.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:19
 */

#ifndef GAMESPEEDESTWIN_H
#define	GAMESPEEDESTWIN_H

#include <SFML/Network/Packet.hpp>

#include "shared/map/Map.h"

#include "server/game/ServerGame.h"

class Server;
class ServerPlayers;
class MapHeader;
class MessageData;
class ServerPlayer;

class ServerGameSpeedestWin : public ServerGame {
public:
    ServerGameSpeedestWin(Server &server, ServerPlayers &players, const MapHeader &header);
    virtual ~ServerGameSpeedestWin();

    const Map& getMap() const;

    virtual bool read(MessageData* message, ServerPlayer* player);
    virtual sf::Packet toPacket(sf::Packet& packet) const;

protected:
    virtual void initGame();
    virtual void startGameLoop();


private:
    Map m_map;
};

sf::Packet& operator<<(sf::Packet& packet, const ServerGameSpeedestWin& game);

#endif	/* GAMESPEEDESTWIN_H */

