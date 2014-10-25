/* 
 * File:   ServerSocketManager.h
 * Author: maxence
 *
 * Created on 13 octobre 2014, 20:39
 */

#ifndef SERVERSOCKETMANAGER_H
#define	SERVERSOCKETMANAGER_H

//#include <thread>
#include <list>

#include "shared/UdpSocketManager.h"
#include "shared/network/EmplifiedSocket.h"
#include "shared/network/SocketReader.h"
#include "server/network/ConnectionEvent.h"

class ConnectionEvent;

class ServerSocketManager  {
    
public:
    ServerSocketManager();
    ServerSocketManager(const ServerSocketManager& orig);
    virtual ~ServerSocketManager();
    
    std::list<SocketQueuBuffer*>& getWaitingClientBuffer();
    std::list<sf::Packet>& getWaitingClientPacket();
    
    void setConnectionListener(ConnectionEvent* connectionListener);
    
    SocketReader* createAndAddConnectionSocket(unsigned short serverPort = UdpSocketManager::serverPort);
    SocketReader* createAndAddCommunicationSocket(const sf::IpAddress &remoteAdress, unsigned short remotePort, unsigned short socketPort = sf::UdpSocket::AnyPort);
    
    void broadcastMessage(sf::Packet &packet);
    
    void acceptPlayers(bool accept);
    
    void startAsychroneReadLoop(void);
    void startReadLoop(void);
    
private:
    
    void readerLoop();
    void receiveConnection();
    void readSelector();
    
    SocketReader* m_connectionReader;
    
    bool m_readerLoop;
    bool m_acceptPlayers;
    //thread* m_readerThread;
    
    ConnectionEvent* m_connectionListener;
    std::vector<SocketReader*> m_communicationReaders;
    sf::SocketSelector m_socketSelector;
    std::list<SocketQueuBuffer*> m_waitingClientBuffer;
    std::list<sf::Packet> m_waitingClientPacket;
    
    

};

#endif	/* SERVERSOCKETMANAGER_H */

