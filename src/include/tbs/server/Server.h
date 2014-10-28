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

class Server {
public:
    Server();
    Server(const Server& orig);
    virtual ~Server();
    
    void start(void);
    void waitConnections(void);
    
private:
    ServerWorld m_world;
    sf::TcpSocket m_clients[100];
    int m_clientsCount;
};

#endif	/* SERVER_H */

