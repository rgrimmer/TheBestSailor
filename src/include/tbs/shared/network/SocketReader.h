/* 
 * File:   SocketReader.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 11:54
 */

#ifndef SOCKETREADER_H
#define	SOCKETREADER_H

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include "shared/network/SocketQueuBuffer.h"

//@TODO Change name to NetworkBuffer
class SocketReader {
public:
    SocketReader(unsigned short remotePort = sf::UdpSocket::AnyPort);
    SocketReader(const sf::IpAddress &remoteAdress, unsigned short remotePort, unsigned short socketPort = sf::UdpSocket::AnyPort);
    SocketReader(const SocketReader& orig);
    virtual ~SocketReader();
    
    SocketQueuBuffer*  getBuffer();
    sf::UdpSocket* getSocket();
    
    void asynchRead();
    void read();
    
    void send(sf::Packet &packet);
private:
    
    unsigned short m_remotePort;
    sf::IpAddress m_remoteAdress;
    SocketQueuBuffer *m_buffer;
    sf::UdpSocket *m_socket;

};

#endif	/* SOCKETREADER_H */

