/* 
 * File:   Server.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:30
 */

#ifndef SERVER_H
#define	SERVER_H

#include <list>
#include <vector>

#include <SFML/Network.hpp>

#include "server/network/ServerTCPManager.h"
#include "server/network/ServerUDPManager.h"
#include "server/ServerPlayer.h"
#include "server/serverCheckpoint/ServerCheckpointManager.h"

#include "shared/map/HeigthMap.h"
#include "shared/SynchronizedQueue.h"

class Server {
public:
    Server();
    virtual ~Server();

    void start(void);
    void waitConnections(sf::Packet packet, std::vector<ServerPlayer*>& players);

private:
    static void receive(ServerUDPManager& udpManager, SynchronizedQueue<sf::Packet>& inQueue);

    ServerTCPManager m_tcpManager;
    ServerUDPManager m_udpManager;

    HeigthMap *m_map;
    ServerCheckpointManager m_checkpointManager;

    SynchronizedQueue<sf::Packet> m_inQueue;

    std::vector<ServerPlayer*> m_players;

};

#endif	/* SERVER_H */

