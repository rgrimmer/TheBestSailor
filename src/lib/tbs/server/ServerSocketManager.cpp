/* 
 * File:   ServerSocketManager.cpp
 * Author: maxence
 * 
 * Created on 13 octobre 2014, 20:39
 */

#include "server/ServerSocketManager.h"
#include <SFML/Network/Packet.hpp>

ServerSocketManager::ServerSocketManager() {
    createAndAddConnectionSocket();
}

ServerSocketManager::ServerSocketManager(const ServerSocketManager& orig) {
}

ServerSocketManager::~ServerSocketManager() {
    m_readerLoop = false;
    //m_readerThread.join();
    
    for(SocketReader* reader : m_communicationReaders) {
        delete(reader);
    }
    delete m_connectionReader;
}

SocketReader* ServerSocketManager::createAndAddConnectionSocket(unsigned short serverPort) {
    m_connectionReader = new SocketReader(sf::IpAddress(), 0, serverPort);
    m_socketSelector.add(*(m_connectionReader->getSocket()));
    return m_connectionReader;
}


SocketReader* ServerSocketManager::createCommunicationSocket(const sf::IpAddress &remoteAdress, unsigned short remotePort, unsigned short socketPort) {
    SocketReader* reader = new SocketReader(remoteAdress, remotePort, socketPort);
    m_communicationReaders.push_back(reader);
    m_socketSelector.add(*reader->getSocket());
    return reader;
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
            for(SocketReader *reader : m_communicationReaders) {
                if(m_socketSelector.isReady(*reader->getSocket())) {
                    reader->asynchRead();
                }
            }
            // Sheach on connection socket
            if(m_socketSelector.isReady(*m_connectionReader->getSocket())) {
                // Not asychrone for update socketSelector
                m_connectionReader->read();
            }
        } else {
            // Timeout
        }
}

void ServerSocketManager::broadcastMessage(sf::Packet &packet) {
    for(SocketReader *reader : m_communicationReaders) {
        reader->send(packet);
    }
}