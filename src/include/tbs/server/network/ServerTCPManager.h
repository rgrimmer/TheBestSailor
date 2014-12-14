/* 
 * File:   ServerTCPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 15:36
 */

#ifndef SERVER_TCP_MANAGER_H
#define	SERVER_TCP_MANAGER_H

#include <SFML/Network.hpp>

#include <server/ServerPlayer.h>

#include "shared/network/Semaphore.h"

class ServerTCPManager {
public:
    ServerTCPManager();
    ~ServerTCPManager();

    bool waitConnections(unsigned short port, std::vector<ServerPlayer*>& players, sf::Time timeout = sf::seconds(5.0f));
    bool send(sf::Packet packet, sf::TcpSocket* player);
    bool send(sf::Packet packet, std::vector<ServerPlayer*> players);
    void waitAcknowledgment(int permits = 1);

private:
    bool receiveNewConnection();
    void receiveCommunication(int& index, std::vector<ServerPlayer*>& players);

    //    unsigned short m_port;
    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;

    sf::TcpSocket m_clients[100];
    std::vector<sf::TcpSocket> m_clientsV;
    int m_clientsCount;
    
    Semaphore m_acknowledgment;
};


#endif	/* SERVER_TCP_MANAGER_H */

