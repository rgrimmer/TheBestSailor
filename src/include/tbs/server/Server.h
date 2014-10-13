/* 
 * File:   Server.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:30
 */

#ifndef SERVER_H
#define	SERVER_H

#include <SFML/Network.hpp>

#include "shared/Map.h"
#include "shared/ConnectionManager.h"

class Server {
public:
    Server();
    Server(const Server& orig);
    virtual ~Server();
    
    void start(void);

private:
    Map *m_map;
    ConnectionManager m_connectionManager;

};

#endif	/* SERVER_H */

