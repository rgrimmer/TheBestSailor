/* 
 * File:   ServerSocketManager.h
 * Author: maxence
 *
 * Created on 13 octobre 2014, 20:39
 */

#ifndef SERVERSOCKETMANAGER_H
#define	SERVERSOCKETMANAGER_H

#include "shared/UdpSocketManager.h"
#include "shared/network/EmplifiedSocket.h"

class ServerSocketManager : public UdpSocketManager {
public:
    ServerSocketManager();
    ServerSocketManager(const ServerSocketManager& orig);
    virtual ~ServerSocketManager();
    
    sf::Socket& addSubscriber(const sf::IpAddress &subscriberAdress, unsigned short subscriberPort);
    void readSubscriber();
    sf::Packet receive();
private:
    sf::UdpSocket m_connectionSocket;
    std::vector<EmplifiedSocket*> m_subscriberSockets;
    sf::SocketSelector m_socketSelector;

};

#endif	/* SERVERSOCKETMANAGER_H */

