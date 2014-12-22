/* 
 * File:   MsgFactory.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 00:40
 */

#ifndef MSGFACTORY_H
#define	MSGFACTORY_H

#include <SFML/Network/Packet.hpp>

#include "shared/network/MsgType.h"

class MessageData;

class MsgFactory {
public:
    static MessageData* createMessage(MsgType msgType);
private:

};

#endif	/* MSGFACTORY_H */
