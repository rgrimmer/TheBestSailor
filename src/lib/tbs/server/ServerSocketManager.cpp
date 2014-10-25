/* 
 * File:   ServerSocketManager.cpp
 * Author: maxence
 * 
 * Created on 13 octobre 2014, 20:39
 */

#include "server/ServerSocketManager.h"

#include <tuple>
#include <iostream>
#include <thread>

#include <SFML/Network/Packet.hpp>

ServerSocketManager::ServerSocketManager() : m_acceptPlayers(false) {
    std::cout << "ServerSocketManager constructor" << std::endl;
    createAndAddConnectionSocket();
}

ServerSocketManager::ServerSocketManager(const ServerSocketManager& orig) {
}

ServerSocketManager::~ServerSocketManager() {
    m_readerLoop = false;
    //m_readerThread.join();

    for (SocketReader* reader : m_communicationReaders) {
        delete(reader);
    }
    delete m_connectionReader;
}

void ServerSocketManager::setConnectionListener(ConnectionEvent* connectionListener) {
    m_connectionListener = connectionListener;
}

SocketReader* ServerSocketManager::createAndAddConnectionSocket(unsigned short serverPort) {
    m_connectionReader = new SocketReader(sf::IpAddress(), 0, serverPort);
    m_socketSelector.add(*(m_connectionReader->getSocket()));
    return m_connectionReader;
}

SocketReader* ServerSocketManager::createAndAddCommunicationSocket(const sf::IpAddress &remoteAdress, unsigned short remotePort, unsigned short socketPort) {
    SocketReader* reader = new SocketReader(remoteAdress, remotePort, socketPort);
    m_communicationReaders.push_back(reader);
    m_socketSelector.add(*reader->getSocket());
    return reader;
}

void ServerSocketManager::readerLoop() {
    while (m_readerLoop) {
        readSelector();
    }
}

void ServerSocketManager::readSelector() {
    // Wait event on socket
    if (m_socketSelector.wait()) {
        // Search on communication socket
        for (SocketReader *reader : m_communicationReaders) {
            if (m_socketSelector.isReady(*reader->getSocket())) {
                reader->asynchRead();
            }
        }
        // Sheach on connection socket
        if (m_socketSelector.isReady(*m_connectionReader->getSocket())) {
            // Not asychrone for update socketSelector
            receiveConnection();
        }
    } else {
        // Timeout
    }
}

void ServerSocketManager::broadcastMessage(sf::Packet &packet) {
    for (SocketReader *reader : m_communicationReaders) {
        reader->send(packet);
    }
}

void ServerSocketManager::receiveConnection() {
    sf::Packet remotePacket;
    unsigned short remotePort;
    sf::IpAddress remoteIpAdress;
    m_connectionReader->getSocket()->receive(remotePacket, remoteIpAdress, remotePort);

    SocketReader *comm = createAndAddCommunicationSocket(remoteIpAdress, remotePort);
    // Transmet comminaction socket to the client
    comm->send(remotePacket);
    if (m_acceptPlayers && m_connectionListener != NULL)
        m_connectionListener->receiveConnection(remotePacket, comm->getBuffer());
    else {
        m_waitingClientBuffer.push_back(comm->getBuffer());
        m_waitingClientPacket.push_back(remotePacket);
    }

}

void ServerSocketManager::startAsychroneReadLoop(void) {
    // @TODO thread
    std::thread *t = new std::thread(&ServerSocketManager::startReadLoop, this);

}

void ServerSocketManager::startReadLoop(void) {
    m_readerLoop = true;
    readerLoop();
}

void ServerSocketManager::acceptPlayers(bool accept) {
    m_acceptPlayers = accept;
}

std::list<SocketQueuBuffer*>& ServerSocketManager::getWaitingClientBuffer() {
    return m_waitingClientBuffer;
}

std::list<sf::Packet>& ServerSocketManager::getWaitingClientPacket() {
    return m_waitingClientPacket;
}