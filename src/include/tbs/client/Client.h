/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include "shared/map/Map.h"
#include "shared/UdpSocketManager.h"

class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();

    void start(void);
private:
    void receiveMap(MapHeader &map, UdpSocketManager &connectionManager);

};

#endif	/* CLIENT_H */

