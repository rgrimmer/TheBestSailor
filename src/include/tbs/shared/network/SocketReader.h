/* 
 * File:   SocketReader.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 11:54
 */

#ifndef SOCKETREADER_H
#define	SOCKETREADER_H

#include <SFML/Network/UdpSocket.hpp>
#include "shared/network/SocketQueuBuffer.h"

class SocketReader {
public:
    SocketReader(SocketQueuBuffer *buffer);
    SocketReader(const SocketReader& orig);
    virtual ~SocketReader();
    
    void setBuffer(SocketQueuBuffer *buffer);
    
    void asynchRead();
    void read();
private:
    
    SocketQueuBuffer *m_buffer;
    sf::UdpSocket *m_socket;

};

#endif	/* SOCKETREADER_H */

