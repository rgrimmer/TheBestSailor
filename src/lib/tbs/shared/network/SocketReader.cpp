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
//: SocketReader(sf::IpAddress(), 0, localPort){
: m_remoteAdress(sf::IpAddress()), m_remotePort(0) {
    m_buffer = new SocketQueuBuffer();
    m_socket = new sf::UdpSocket();
    m_socket->bind(localPort);
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

void SocketReader::setRemoteAdress(const sf::IpAddress &remoteAdress) {
    m_remoteAdress = remoteAdress;
}

void SocketReader::setRemotePort(unsigned short remotePort) {
    m_remotePort = remotePort;
}

/* Start a thread for read data
 */
void SocketReader::asynchRead() {
    // std::thread t(&SocketReader::read, this);
    // @TODO : probably add t.join(); in destructor
}

//
//#include <iostream>
//#include "shared/map/MapHeader.h"
//sf::Packet& operator>>(sf::Packet &packet, MapHeader &header) {
//    std::cout << packet.getDataSize() << std::endl;
//
//    //assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);
//
//    sf::Int32 mapWidth;
//    sf::Int32 mapHeight;
//    sf::Int32 mapSeed;
//
//    packet >> mapSeed >> mapHeight >> mapWidth;
//
//
//    header = MapHeader(mapWidth, mapHeight, mapSeed);
//
//    std::cout << "packet to map : " << mapWidth << " " << mapHeight << " " << mapSeed << std::endl;
//
//    return packet;
//}

void SocketReader::read() {
    sf::Packet packetReceive;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;

    m_socket->receive(packetReceive, remoteAddress, remotePort);
    m_buffer->pushBack(packetReceive);
//    
//    MapHeader h;
//    packetReceive >> h;
//    std::cout << h.getHeight() << " " << h.getWidth() << " " << h.getSeed() << std::endl;
}

void SocketReader::send(sf::Packet &packet) {
    m_socket->send(packet, m_remoteAdress, m_remotePort);
}
