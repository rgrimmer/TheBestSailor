/* 
 * File:   Requests.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 17:14
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include <SFML/Network.hpp>

typedef enum {
    REQ_NEW_PLAYER,
    REQ_IDENT,
    REQ_ACTION_TURN_HELM_POSITIVE,
    REQ_ACTION_TURN_HELM_NEGATIVE,
    REQ_ACTION_TURN_SAIL_POSITIVE,
    REQ_ACTION_TURN_SAIL_NEGATIVE
} reqType;

class Request {
public:
    explicit Request(reqType type, unsigned int id);
    virtual ~Request();

    virtual sf::Packet createPacket();
protected:
    reqType m_type;
    unsigned int m_id;
};

#endif	/* REQUEST_H */

