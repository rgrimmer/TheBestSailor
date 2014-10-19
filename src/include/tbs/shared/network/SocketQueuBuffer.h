/* 
 * File:   SocketQueuBuffer.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 11:57
 */

#ifndef SOCKETQUEUBUFFER_H
#define	SOCKETQUEUBUFFER_H

#include <list>
#include <SFML/Network/Packet.hpp>

class SocketQueuBuffer : public std::list<sf::Packet> {
public:
    SocketQueuBuffer();
    SocketQueuBuffer(const SocketQueuBuffer& orig);
    virtual ~SocketQueuBuffer();
private:

};

#endif	/* SOCKETQUEUBUFFER_H */

