/* 
 * File:   ServerNetwork.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 13:32
 */

#ifndef SERVERNETWORK_H
#define	SERVERNETWORK_H

#include <thread>

#include "server/network/ServerUDPManager.h"
#include "server/network/ServerTCPManager.h"
#include "server/network/ServerMessageQueue.h"

class ServerPlayers;

class ServerNetwork {
public:
    ServerNetwork(ServerPlayers &players);
    virtual ~ServerNetwork();

    void initialize();

    ServerTCPManager& getTCPManager();
    ServerUDPManager& getUDPManager();
    ServerMessageQueue& getMessageQueue();

private:
    void startTCPThread();
    void startUDPThread();
    void tcpReceiveLoop();
    void udpReceiveLoop();

private:
    ServerPlayers& m_players;

    ServerMessageQueue m_messageQueue;

    ServerTCPManager m_tcpManager;
    ServerUDPManager m_udpManager;
    
    std::thread *m_threadTCP;
    std::thread *m_threadUDP;
};

#endif	/* SERVERNETWORK_H */

