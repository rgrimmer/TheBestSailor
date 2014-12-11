/* 
 * File:   Requests.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 17:14
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include <SFML/Network.hpp>

#include "RequestData.h"

class Request {
public:
    static unsigned int popID(sf::Packet& packet);
public:
    explicit Request(unsigned int id, const RequestData &data);
    virtual ~Request();

    sf::Packet getPacket() const;
protected:
    unsigned int m_id;
    const RequestData *m_data;
};

#endif	/* REQUEST_H */

