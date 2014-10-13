/* 
 * File:   ConnectionManager.h
 * Author: maxence
 *
 * Created on 11 octobre 2014, 20:10
 */

#ifndef CONNECTIONMANAGER_H
#define	CONNECTIONMANAGER_H

#include <vector>
#include <tuple>

#include <SFML/Network/IpAddress.hpp>


class ConnectionManager {
public:
    static const unsigned short serverPort = 1234;
    static const sf::IpAddress serverAddress;
    static const unsigned short clientPort = 1248;
    static const sf::IpAddress clientAddress;
    
public:
    ConnectionManager();
    ConnectionManager(const ConnectionManager& orig);
    virtual ~ConnectionManager();
    
    void addRemote(const sf::IpAddress &remoteAddress, unsigned short remotePort);
    
    void bind(unsigned short socketPort);
    
    void receive(sf::Packet &packet, sf::IpAddress &remoteAddress, unsigned short &remotePort);
    void receive(const void *data, std::size_t size, sf::IpAddress &remoteAddress, unsigned short &remotePort);
    
    void send(const sf::Packet &packet);
    void send(const void *data, std::size_t size);
    void send(const sf::Packet &packet, const sf::IpAddress &remoteAddress, unsigned short remotePort);
    void send(const void *data, std::size_t size, const sf::IpAddress &remoteAddress, unsigned short remotePort);

    
private:
    std::vector<std::pair<const sf::IpAddress, unsigned short> > connections;
    sf::UdpSocket m_socket;
    

};

#endif	/* CONNECTIONMANAGER_H */

