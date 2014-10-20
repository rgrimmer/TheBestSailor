/* 
 * File:   SocketReader.cpp
 * Author: maxence
 * 
 * Created on 19 octobre 2014, 11:54
 */

#include "shared/network/SocketReader.h"

//#include <thread>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/IpAddress.hpp>

SocketReader::SocketReader(unsigned short localPort) 
: SocketReader(sf::IpAddress(), 0, localPort){
    
}

SocketReader::SocketReader(const sf::IpAddress &remoteAdress, unsigned short remotePort, unsigned short socketPort)
: m_remoteAdress(remoteAdress), m_remotePort(remotePort) {
    m_buffer = new SocketQueuBuffer();
    m_socket = new sf::UdpSocket();
    m_socket->bind(socketPort);
}

SocketReader::SocketReader(const SocketReader& orig) {

}

SocketReader::~SocketReader() {
    delete m_buffer;
    delete m_socket;
}

SocketQueuBuffer* SocketReader::getBuffer() {
    return m_buffer;
}

sf::UdpSocket* SocketReader::getSocket() {
    return m_socket;
}

/* Start a thread for read data
 */
void SocketReader::asynchRead() {
    // std::thread t(&SocketReader::read, this);
    // @TODO : probably add t.join(); in destructor
}

void SocketReader::read() {
    sf::Packet packetReceive;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;

    m_socket->receive(packetReceive, remoteAddress, remotePort);
    m_buffer->push_back(packetReceive);
}

void SocketReader::send(sf::Packet &packet) {
    m_socket->send(packet, m_remoteAdress, m_remotePort);
}
