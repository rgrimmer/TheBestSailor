/* 
 * File:   ServerSocketManager.h
 * Author: maxence
 *
 * Created on 13 octobre 2014, 20:39
 */

#ifndef SERVERSOCKETMANAGER_H
#define	SERVERSOCKETMANAGER_H

//#include <thread>

#include "shared/UdpSocketManager.h"
#include "shared/network/EmplifiedSocket.h"
#include "shared/network/SocketReader.h"


class ServerSocketManager  {
    
public:
    ServerSocketManager();
    ServerSocketManager(const ServerSocketManager& orig);
    virtual ~ServerSocketManager();
    
    SocketReader* createAndAddConnectionSocket(unsigned short serverPort = UdpSocketManager::serverPort);
    SocketReader* createCommunicationSocket(const sf::IpAddress &remoteAdress, unsigned short remotePort, unsigned short socketPort = sf::UdpSocket::AnyPort);
    
    void broadcastMessage(sf::Packet &packet);
    
private:
    
    void readSelector();
    void readerLoop();
    
    SocketReader* m_connectionReader;
    
    bool m_readerLoop;
    //thread* m_readerThread;
    std::vector<SocketReader*> m_communicationReaders;
    sf::SocketSelector m_socketSelector;
    
    

};

#endif	/* SERVERSOCKETMANAGER_H */

