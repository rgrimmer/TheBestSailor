/* 
 * File:   ServerNetwork.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 13:32
 */

#ifndef SERVERNETWORK_H
#define	SERVERNETWORK_H

#include <thread>

#include "shared/network/UtilsNetwork.h"
#include "shared/SynchronizedQueue.h"

#include "server/Server.h"
#include "server/network/ServerTCPManager.h"
#include "server/network/ServerUDPManager.h"


class Server;

class ServerNetwork {
public:
    ServerNetwork(Server &server);
    virtual ~ServerNetwork();
    
    void initialize();


    // Temporary
    void waitConnection();
    void broadcastGame();
    void mainLoop();

private:
    void startTCPThread();
    void startUDPThread();
    void tcpReceiveLoop();
    void udpReceiveLoop();
private:
    Server &m_server;
    ServerTCPManager m_tcpManager;
    ServerUDPManager m_udpManager;

    std::thread *m_threadTCP;
    std::thread *m_threadUDP;
    SynchronizedQueue<sf::Packet> m_inQueue;
};

#endif	/* SERVERNETWORK_H */

