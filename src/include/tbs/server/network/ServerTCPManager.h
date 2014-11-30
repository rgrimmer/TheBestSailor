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

class ServerTCPManager {
public:
    ServerTCPManager();
    ~ServerTCPManager();

    bool initialize(unsigned short port);
    bool waitConnections(sf::Packet packet, std::vector<ServerPlayer*>& players);
    bool send (sf::Packet packet, sf::TcpSocket* player);
    
private:

    unsigned short m_port;
    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;

    sf::TcpSocket m_clients[100];
    int m_clientsCount;
};


#endif	/* SERVER_TCP_MANAGER_H */

