/* 
 * File:   Message.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 17:14
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include <SFML/Network.hpp>

#include "MessageData.h"

#define ID_SF_CAST sf::Uint8

class Message {
public:
    static unsigned int popID(sf::Packet& packet);
public:
    explicit Message(unsigned int id, const MessageData &data);
    virtual ~Message();

    sf::Packet getPacket() const;
    MsgType getType() const;
    
protected:
    unsigned int m_id;
    const MessageData *m_data;
};

#endif	/* MESSAGE_H */

