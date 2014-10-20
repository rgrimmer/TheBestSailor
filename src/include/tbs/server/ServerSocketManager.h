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
    
    sf::Socket& addSubscriber(const sf::IpAddress &subscriberAdress, unsigned short subscriberPort);
    sf::Packet receive();
    
private:
    
    void readSelector();
    void readerLoop();
    sf::UdpSocket m_connectionSocket;
    std::vector<EmplifiedSocket*> m_subscriberSockets;
    sf::SocketSelector m_socketSelector;
    
    bool m_readerLoop;
    //thread* m_readerThread;
    SocketReader m_reader;
    //New
    //@TODO : Buffer de connection
    //@TODO : socket de connection
    //@TODO : vecteur de buffer de com
    //@TODO : vecteur de socket de com
    
    //@TODO : Connection : retourne un buffer sur lequel sera
    // enregistré les infos envoyés par les joueurs
    

};

#endif	/* SERVERSOCKETMANAGER_H */

