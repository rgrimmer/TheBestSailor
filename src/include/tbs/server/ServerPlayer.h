/* 
 * File:   ServerPlayer.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 16:29
 */

#ifndef SERVER_PLAYER_H
#define	SERVER_PLAYER_H

#include <SFML/Network.hpp>

class ServerPlayer {
public:
    ServerPlayer(unsigned int id, std::string name, sf::TcpSocket* socket);
    ~ServerPlayer();

    void setUdpPort(unsigned short port);
    sf::TcpSocket* getTCPSocket() const;
    sf::IpAddress getAddress() const;
    std::string getName() const;
    unsigned short getUdpPort() const;
    
private:
    unsigned int m_id;
    std::string m_name;
    sf::TcpSocket* m_TCPSocket;
    sf::IpAddress m_address;
    unsigned short int m_udpPort;


};

#endif	/* SERVER_PLAYER_H */

