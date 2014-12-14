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

    bool waitConnections(unsigned short port, std::vector<ServerPlayer*>& players, sf::Time timeout = sf::seconds(5.0f));
    bool send(sf::Packet packet, sf::TcpSocket* player);

private:
    bool receiveNewConnection();
    void receiveCommunication(int& index, std::vector<ServerPlayer*>& players);

    //    unsigned short m_port;
    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;

    sf::TcpSocket m_clients[100];
    int m_clientsCount;
};


#endif	/* SERVER_TCP_MANAGER_H */

