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

#include "shared/entity/map/HeigthMap.h"
#include "server/ServerSocketManager.h"
#include "server/player/PlayerManager.h"
#include "server/network/ConnectionEvent.h"
#include "shared/entity/checkpoint/CheckpointManager.h"

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


    void createCheckpoints();
    
private:
    HeigthMap *m_map;
//    World m_world;
    ServerSocketManager m_clientManager;
    PlayerManager m_players;
    CheckpointManager m_checkpointManager;

};

#endif	/* SERVER_H */

