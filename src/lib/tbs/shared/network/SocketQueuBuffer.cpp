/* 
 * File:   SocketQueuBuffer.cpp
 * Author: maxence
 * 
 * Created on 19 octobre 2014, 11:57
 */

#include "shared/network/SocketQueuBuffer.h"

SocketQueuBuffer::SocketQueuBuffer() {
}

SocketQueuBuffer::SocketQueuBuffer(const SocketQueuBuffer& orig) {
}

SocketQueuBuffer::~SocketQueuBuffer() {
}

sf::Packet SocketQueuBuffer::pop(void) {
    sf::Packet packet = m_queue.front();
    m_queue.pop();
    return packet;
}

void SocketQueuBuffer::pushBack(const sf::Packet &packet) {
    m_queue.push(packet);
}
