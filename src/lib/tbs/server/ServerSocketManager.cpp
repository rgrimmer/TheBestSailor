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

void ServerSocketManager::readSubscriber() {
    sf::Packet subPacket;
    sf::IpAddress subAdress;
    unsigned short subPort;
    m_connectionSocket.receive(subPacket, subAdress, subPort);
    addSubscriber(subAdress, subPort);
}

/* Attente d'une activité
 */
sf::Packet ServerSocketManager::receive() {
    // @TODO, comportement différent en fonction du gameState
    
    // Comportement pour : Une carte déjà généré. On l'envoi a tout ceux qui ce connect
    m_socketSelector.wait();
    
    if(m_socketSelector.isReady(m_connectionSocket))
        readSubscriber();
    
        // @TODO
    return sf::Packet();
}
