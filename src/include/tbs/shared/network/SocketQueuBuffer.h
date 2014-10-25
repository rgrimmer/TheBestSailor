/* 
 * File:   SocketQueuBuffer.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 11:57
 */

#ifndef SOCKETQUEUBUFFER_H
#define	SOCKETQUEUBUFFER_H

#include <queue>
#include <SFML/Network/Packet.hpp>

class SocketQueuBuffer {
public:
    SocketQueuBuffer();
    SocketQueuBuffer(const SocketQueuBuffer& orig);
    virtual ~SocketQueuBuffer();
    
    sf::Packet pop(void);
    void pushBack(const sf::Packet &packet);
private:
    std::queue<sf::Packet> m_queue;

};

#endif	/* SOCKETQUEUBUFFER_H */

