/* 
 * File:   MsgFactory.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 00:40
 */

#ifndef MSGFACTORY_H
#define	MSGFACTORY_H

#include <SFML/Network/Packet.hpp>

class MessageData;

class MsgFactory {
public:
    static MessageData* createMessage(sf::Packet& packet);
private:

};

#endif	/* MSGFACTORY_H */

