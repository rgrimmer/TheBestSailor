/* 
 * File:   ServerPlayer.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 16:29
 */

#ifndef SERVER_PLAYER_H
#define	SERVER_PLAYER_H

#include <SFML/Network.hpp>

#include "shared/network/MsgClientPlayerInfo.h"

class ServerPlayer {
public:
    ServerPlayer();
    ~ServerPlayer();

    void setUdpPort(unsigned short port);
    sf::TcpSocket& getTCPSocket();
    const sf::TcpSocket& getTCPSocket() const;
    sf::IpAddress getAddress() const;
    std::string getName() const;
    void setName(const std::string &name);
    unsigned int getId() const;
    unsigned short getUdpPort() const;

private:
    unsigned int m_id;
    std::string m_name;
    unsigned short int m_udpPort;
    sf::TcpSocket m_TCPSocket;


};

//MsgClientPlayerInfo operator>>(MsgClientPlayerInfo &msg, ServerPlayer player);

#endif	/* SERVER_PLAYER_H */

