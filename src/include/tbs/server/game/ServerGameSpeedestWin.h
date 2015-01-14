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

#include "server/serverCheckpoint/ServerCheckpointManager.h"
#include "server/serverCheckpoint/ServerCheckpoint.h"

#include "server/game/ServerGame.h"

class Server;
class ServerPlayer;
class ServerPlayers;
class MapHeader;
class MsgData;
class Ship;

class ServerGameSpeedestWin : public ServerGame {
public:
    ServerGameSpeedestWin(Server &server, ServerPlayers &players, const MapHeader &header);
    ServerGameSpeedestWin(const ServerGameSpeedestWin& other);
    virtual ~ServerGameSpeedestWin();

    const Map& getMap() const;

protected:
    virtual bool read(MsgData& message, ServerPlayer& player);

    virtual void init();
    virtual void update(float dt);
    virtual void sendGame();
    virtual void sendInfo();
    virtual bool gameIsEnded();

private:
    void updateShipState(Ship& ship, float dt);
    void updateSail(Ship& ship);
    sf::Vector2f calculShipVelocity(Ship& ship);

    bool collideWithMap(const Ship & ship, const sf::Vector2f & velocity);
    bool collideWithCheckPoint(const Ship & ship, const ServerCheckpoint & checkPoint);
    
    bool readAction(MsgData& msg, ServerPlayer& player);
    bool readDisconnect(MsgData& msg, ServerPlayer& player);

    bool windComeFromTribord(const Ship& ship, const Wind &wind) const;
    bool windComeFromFront(const Ship& ship, const Wind &wind) const;

    
private:
    Map m_map;
    ServerCheckpointManager m_checkPointManager;
    std::map<ServerPlayer*, Ship> m_ships;
    
    sf::Clock m_gameClock;
    std::map<ServerPlayer*, sf::Time> m_lastAction;
};

sf::Packet& operator<<(sf::Packet& packet, const ServerGameSpeedestWin& game);

#endif	/* GAMESPEEDESTWIN_H */

