/* 
 * File:   ServerSocketManager.cpp
 * Author: maxence
 * 
 * Created on 13 octobre 2014, 20:39
 */

#include "server/ServerSocketManager.h"
#include <SFML/Network/Packet.hpp>

ServerSocketManager::ServerSocketManager() {
    m_connectionSocket.bind(UdpSocketManager::serverPort);
}

ServerSocketManager::ServerSocketManager(const ServerSocketManager& orig) {
}

ServerSocketManager::~ServerSocketManager() {
    m_readerLoop = false;
    //m_readerThread.join();
    
    for(sf::Socket* subscriberSocket : m_subscriberSockets) {
        delete(subscriberSocket);
    }
}

void createSocket() {
    
}

/* @brief Call when a new client send message on the connectionSocket
 * @return the communication socket for the client
 */
sf::Socket& ServerSocketManager::addSubscriber(const sf::IpAddress &subscriberAdress, unsigned short subscriberPort) {
    // Create the communication socket
    EmplifiedSocket *commSocket = new EmplifiedSocket(subscriberAdress, subscriberPort);
    commSocket->bind(sf::UdpSocket::AnyPort);
    
    // Add to the subscriber list
    m_subscriberSockets.push_back(commSocket);
    
    // Add to the selector
    m_socketSelector.add(*commSocket);
    
    // @TODO save ip and port of the subscriber
    
    return *commSocket;
}


void ServerSocketManager::readerLoop() {
    while(m_readerLoop) {
        readSelector();
    }
}

void ServerSocketManager::readSelector() {
    // Wait event on socket
    if(m_socketSelector.wait()) {
            // Search on communication socket
            for(sf::Socket *socket : m_subscriberSockets) {
                if(m_socketSelector.isReady(*socket)) {
                    m_reader.asynchRead();
                }
            }
            // Sheach on connection socket
            if(m_socketSelector.isReady(m_connectionSocket))
                // Not asychrone for update socketSelector
                m_reader.read();
            
        } else {
            // Timeout
        }
}