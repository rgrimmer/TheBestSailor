/* 
 * File:   ConnectionManager.cpp
 * Author: maxence
 * 
 * Created on 11 octobre 2014, 20:10
 */
#include "shared/UdpSocketManager.h"

#include <unistd.h>
#include <iostream>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>



const sf::IpAddress UdpSocketManager::serverAddress = "localhost";
const sf::IpAddress UdpSocketManager::clientAddress = "localhost";

UdpSocketManager::UdpSocketManager() {
    m_receiver = new RemoteList();
}

UdpSocketManager::UdpSocketManager(const UdpSocketManager& orig) {
}

UdpSocketManager::~UdpSocketManager() {

}

void UdpSocketManager::addRemote(const sf::IpAddress &remoteAddress, unsigned short remotePort) {
    m_receiver->push_back(Remote(remoteAddress, remotePort));
}

void UdpSocketManager::bind(unsigned short socketPort) {
    m_socket.bind(socketPort);
    m_selector.add(m_socket);
}

void UdpSocketManager::connectTo(const sf::IpAddress &remoteAdress, unsigned short remotePort) {
    // @TODO send message
    send(sf::Packet(), remoteAdress, remotePort);
    addRemote(remoteAdress, remotePort);
}


void UdpSocketManager::receive(sf::Packet &packet) {
    
}


void UdpSocketManager::receive(sf::Packet &packet, sf::IpAddress &remoteAddress, unsigned short &remotePort) {
    std::cout << "wait recevie" << remoteAddress << " " << remotePort << std::endl;
    int count = 1;
    m_socket.receive(packet, remoteAddress, remotePort);
    std::cout << "1 recevie " << packet.getDataSize() << std::endl;
    if (packet.getDataSize() == sf::UdpSocket::MaxDatagramSize) {
        sf::Packet subPacket;
        do {
            std::cout << "do recevie" << std::endl;
            subPacket = sf::Packet();
            m_socket.receive(subPacket, remoteAddress, remotePort);
            count++;
            std::cout << count << std::endl;
            packet.append(subPacket.getData(), subPacket.getDataSize());
            std::cout << "recevied : " << subPacket.getDataSize() << " " << sf::UdpSocket::MaxDatagramSize << std::endl;
        } while (subPacket.getDataSize() == sf::UdpSocket::MaxDatagramSize);
    }
}

void UdpSocketManager::receive(const void *data, std::size_t size, sf::IpAddress &remoteAddress, unsigned short &remotePort) {
    // @TODO
}

void UdpSocketManager::send(const sf::Packet &packet) {
    for (const Remote &remote : *m_receiver) {
        std::cout << "send to " << remote.first << " " << remote.second << std::endl;
        send(packet, remote.adress(), remote.port());
    }
}

void UdpSocketManager::send(const void *data, std::size_t size) {
    for (const Remote &remote : *m_receiver) {
        send(data, size, remote.adress(), remote.port());
    }
}

void UdpSocketManager::send(const sf::Packet &packet, const sf::IpAddress &remoteAddress, unsigned short remotePort) {

    std::size_t size = packet.getDataSize();
    const void *data = packet.getData();
    int count = 0;
    std::cout << "send : " << size << " at " << data << std::endl;
    // Tantque les donnée sont superieur a la taille max d'un datagramme, 
    // on rempli des datagrammes complet
    while (size >= sf::UdpSocket::MaxDatagramSize) {
        count++;
        sf::Packet subPacket;
        subPacket.append(data, sf::UdpSocket::MaxDatagramSize);
        m_socket.send(subPacket, remoteAddress, remotePort);
        data = (char*) data + sf::UdpSocket::MaxDatagramSize;
        size -= sf::UdpSocket::MaxDatagramSize;
        std::cout << "while : " << size << " " << data << std::endl;
        std::cout << count << std::endl;
        usleep(5000);
    }

    std::cout << count << std::endl;
    sf::Packet subPacket;
    subPacket.append(data, size);
    m_socket.send(subPacket, remoteAddress, remotePort);
}

void UdpSocketManager::send(const void *data, std::size_t size, const sf::IpAddress &remoteAddress, unsigned short remotePort) {

    while (size >= sf::UdpSocket::MaxDatagramSize) {
        m_socket.send(data, sf::UdpSocket::MaxDatagramSize, remoteAddress, remotePort);
        data = (char*) data + sf::UdpSocket::MaxDatagramSize;
        size -= sf::UdpSocket::MaxDatagramSize;
    }

    m_socket.send(data, size, remoteAddress, remotePort);
}