/* 
 * File:   ServerUDPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 15:36
 */

#ifndef SERVER_UDP_MANAGER_H
#define	SERVER_UDP_MANAGER_H

#include <SFML/Network.hpp>

#include <server/ServerPlayer.h>

class ServerUDPManager {
public:
    ServerUDPManager();
    ~ServerUDPManager();

    bool initialize(unsigned short port);

    bool send(sf::Packet packet, const sf::IpAddress & address, unsigned short port);
    
    bool receiveIdentifyRequests(std::vector<ServerPlayer*> players);
    sf::Packet receive(void);
    
private:
    unsigned short m_port;
    sf::UdpSocket m_socket;
};

#endif	/* SERVER_UDP_MANAGER_H */

