/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include "shared/entity/map/Map.h"
#include "shared/UdpSocketManager.h"
#include "shared/network/SocketReader.h"
#include "shared/entity/Player.h"

class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();

    void start(void);
private:
    Map* receiveMap();
    void sendConnectionToServer(void);
    void receiveCommSocket(void);
    
private:
    UdpSocketManager m_commManager;
    SocketReader m_socketReader;
    Player m_player;

};

#endif	/* CLIENT_H */

