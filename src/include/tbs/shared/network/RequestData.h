/* 
 * File:   RequestBody.h
 * Author: maxence
 *
 * Created on 11 décembre 2014, 16:35
 */

#ifndef REQUESTDATA_H
#define	REQUESTDATA_H

#include <SFML/Network/Packet.hpp>

typedef enum {
    REQ_UNDEF,
    REQ_DISCONNECT,
    REQ_NEW_PLAYER,
    REQ_IDENT,
    REQ_ACTION_TURN_HELM,
    REQ_ACTION_TURN_SAIL
} reqType;

typedef enum {
    UNDEF,
    POSITIVE,
    NEGATIVE
} reqOrientation;

#define ORIENTATION_SF_CAST sf::Int8
class RequestData {
public :
    static reqType popType(sf::Packet &packet);
    
public:
    RequestData();
    virtual ~RequestData();

    
    sf::Packet& toPacketWithoutType(sf::Packet &packet) const;
    sf::Packet& toPacketWithType(sf::Packet &packet) const;
        sf::Packet& fromPacketWithoutType(sf::Packet &packet);
        sf::Packet& fromPacketWithType(sf::Packet &packet);

public:
    virtual reqType getType() const =0;

protected:
    sf::Packet& putSfType(sf::Packet &packet) const;
    virtual void getDataFrom(sf::Packet &packet) =0;
    virtual void putDataIn(sf::Packet &packet) const =0;
};

#endif	/* REQUESTDATA_H */

