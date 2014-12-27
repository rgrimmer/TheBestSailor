/* 
 * File:   ServerGameSpeedestWin.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:19
 */

#ifndef GAMESPEEDESTWIN_H
#define	GAMESPEEDESTWIN_H

#include <map>
#include <SFML/Network/Packet.hpp>

#include "shared/map/Map.h"
#include "server/game/ServerGame.h"

class Server;
class ServerPlayer;
class ServerPlayers;
class MapHeader;
class MessageData;
class Ship;

class ServerGameSpeedestWin : public ServerGame {
public:
    ServerGameSpeedestWin(Server &server, ServerPlayers &players, const MapHeader &header);
    virtual ~ServerGameSpeedestWin();

    const Map& getMap() const;

protected:
    virtual sf::Packet toPacket(sf::Packet& packet) const;
    virtual bool read(MessageData& message, ServerPlayer& player);

    virtual void init();
    virtual void update(float dt);
    virtual void sendInfo();
    virtual bool gameIsEnded();

private:
    void updateShipState(Ship& ship, float dt);
    void updateSail(Ship& ship);
    void updateShipVelocity(Ship& ship);
    
    bool readAction(MessageData& msg, ServerPlayer& player);

    bool windComeFromTribord(const Ship& ship, const Wind &wind) const;
    bool windComeFromFront(const Ship& ship, const Wind &wind) const;

private:
    Map m_map;
    std::map<ServerPlayer*, Ship> m_ships;
};

sf::Packet& operator<<(sf::Packet& packet, const ServerGameSpeedestWin& game);

#endif	/* GAMESPEEDESTWIN_H */

