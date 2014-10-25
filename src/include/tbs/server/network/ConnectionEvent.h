/* 
 * File:   ConnectionEvent.h
 * Author: maxence
 *
 * Created on 20 octobre 2014, 19:03
 */

#ifndef CONNECTIONEVENT_H
#define	CONNECTIONEVENT_H

#include <SFML/Network/Packet.hpp>
#include "shared/network/SocketQueuBuffer.h"

class ConnectionEvent {
public:
    virtual void receiveConnection(sf::Packet &packet, SocketQueuBuffer* buffer) = 0;
private:

};

#endif	/* CONNECTIONEVENT_H */

