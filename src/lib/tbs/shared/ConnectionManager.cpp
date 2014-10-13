/* 
 * File:   ConnectionManager.cpp
 * Author: maxence
 * 
 * Created on 11 octobre 2014, 20:10
 */

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>

#include <iostream>

#include "shared/ConnectionManager.h"

const sf::IpAddress ConnectionManager::serverAddress = "localhost";
const sf::IpAddress ConnectionManager::clientAddress = "localhost";


ConnectionManager::ConnectionManager() {
}

ConnectionManager::ConnectionManager(const ConnectionManager& orig) {
}

ConnectionManager::~ConnectionManager() {

}

void ConnectionManager::bind(unsigned short socketPort) {
    m_socket.bind(socketPort);
}

void ConnectionManager::addRemote(const sf::IpAddress &remoteAddress, unsigned short remotePort) {
    connections.push_back(std::pair<sf::IpAddress, unsigned short>(remoteAddress, remotePort));
}


void ConnectionManager::receive(sf::Packet &packet, sf::IpAddress &remoteAddress, unsigned short &remotePort) {
    std::cout << "wait recevie" << std::endl;
    m_socket.receive(packet, remoteAddress, remotePort);
    std::cout << "1 recevie " << packet.getDataSize()  << std::endl;
    if (packet.getDataSize() == sf::UdpSocket::MaxDatagramSize) {
        sf::Packet subPacket;
        do {
            std::cout << "do recevie" << std::endl;
            subPacket = sf::Packet();
            m_socket.receive(subPacket, remoteAddress, remotePort);
            packet.append(subPacket.getData(), subPacket.getDataSize());
            std::cout << "recevied : " << subPacket.getDataSize() << " " << sf::UdpSocket::MaxDatagramSize << std::endl;
        } while (subPacket.getDataSize() == sf::UdpSocket::MaxDatagramSize);
    }
}

void ConnectionManager::receive(const void *data, std::size_t size, sf::IpAddress &remoteAddress, unsigned short &remotePort) {
    // @TODO
}

void ConnectionManager::send(const sf::Packet &packet) {
    for (const std::pair<sf::IpAddress, unsigned short> &remote : connections) {
        std::cout << "send to " << remote.first << " " << remote.second << std::endl;
        send(packet, remote.first, remote.second);
    }
}

void ConnectionManager::send(const void *data, std::size_t size) {
    for (const std::pair<sf::IpAddress, unsigned short> &remote : connections) {
        send(data, size, remote.first, remote.second);
    }
}

void ConnectionManager::send(const sf::Packet &packet, const sf::IpAddress &remoteAddress, unsigned short remotePort) {

    std::size_t size = packet.getDataSize();
    const void *data = packet.getData();

    std::cout << "send : " << size << " at " << data << std::endl;
    // Tantque les donnée sont superieur a la taille max d'un datagramme, 
    // on rempli des datagrammes complet
    while (size >= sf::UdpSocket::MaxDatagramSize) {
        sf::Packet subPacket;
        subPacket.append(data, sf::UdpSocket::MaxDatagramSize);
        m_socket.send(subPacket, remoteAddress, remotePort);
        data = (char*) data + sf::UdpSocket::MaxDatagramSize;
        size -= sf::UdpSocket::MaxDatagramSize;
        std::cout << "while : " << size << " " << data << std::endl;
    }

    sf::Packet subPacket;
    subPacket.append(data, size);
    m_socket.send(subPacket, remoteAddress, remotePort);
}

void ConnectionManager::send(const void *data, std::size_t size, const sf::IpAddress &remoteAddress, unsigned short remotePort) {

    while (size >= sf::UdpSocket::MaxDatagramSize) {
        m_socket.send(data, sf::UdpSocket::MaxDatagramSize, remoteAddress, remotePort);
        data = (char*) data + sf::UdpSocket::MaxDatagramSize;
        size -= sf::UdpSocket::MaxDatagramSize;
    }

    m_socket.send(data, size, remoteAddress, remotePort);
}