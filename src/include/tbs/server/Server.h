/* 
 * File:   Server.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:30
 */

#ifndef SERVER_H
#define	SERVER_H

#include <list>

#include <SFML/Network.hpp>

#include "server/ServerWorld.h"
#include "server/ServerSocketManager.h"
#include "server/player/PlayerManager.h"
#include "server/network/ConnectionEvent.h"

class ConnectionEvent;
class ServerSocketManager;

class Server : public ConnectionEvent {
public:
    Server();
    Server(const Server& orig);
    virtual ~Server();
    
    void start(void);
    void waitPlayers(void);
    void addWaitingPlayers(void);
    

    void receiveConnection(sf::Packet& packet, SocketQueuBuffer* buffer);
    
private:

    ServerSocketManager m_clientManager;
    PlayerManager m_players;
    ServerWorld m_world;

};

#endif	/* SERVER_H */

