/* 
 * File:   SocketReader.cpp
 * Author: maxence
 * 
 * Created on 19 octobre 2014, 11:54
 */

#include "shared/network/SocketReader.h"

#include <thread>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/IpAddress.hpp>

SocketReader::SocketReader(SocketQueuBuffer *buffer) : m_buffer(buffer)
{
}

SocketReader::SocketReader(const SocketReader& orig) {
}

SocketReader::~SocketReader() {
}

void SocketReader::setBuffer(SocketQueuBuffer *buffer) {
    m_buffer = buffer;
}

/* Start a thread for read data
 */
void SocketReader::asynchRead() {
    std::thread t(&SocketReader::read, this);
    // @TODO : probably add t.join(); in destructor
}

void SocketReader::read() {
    sf::Packet packetReceive; 
    sf::IpAddress remoteAddress;
    unsigned short remotePort;
    
    m_socket->receive(packetReceive, remoteAddress, remotePort);
    m_buffer->push_back(packetReceive);
}