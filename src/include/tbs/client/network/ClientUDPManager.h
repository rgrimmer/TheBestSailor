/* 
 * File:   ClientUDPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 14:13
 */

#ifndef CLIENT_UDP_MANAGER_H
#define	CLIENT_UDP_MANAGER_H

#include <SFML/Network.hpp>

class ClientUDPManager {
public:
    ClientUDPManager();
    ~ClientUDPManager();

    void initialize(const std::string& address, unsigned short port);

    bool send (sf::Packet packet);
    sf::Packet receive(void);
    
private:
    sf::IpAddress m_address;
    sf::UdpSocket m_socket;
    unsigned short m_port;

};

#endif	/* CLIENTUDPMANAGER_H */

