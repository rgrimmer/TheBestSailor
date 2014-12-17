/* 
 * File:   MessageData.h
 * Author: maxence
 *
 * Created on 11 décembre 2014, 16:35
 */

#ifndef MESSAGEDATA_H
#define	MESSAGEDATA_H

#include <SFML/Network/Packet.hpp>

typedef enum {
    MSG_UNDEF,
    MSG_DISCONNECT,
    MSG_CLIENT_PLAYER_INFO,
    MSG_SERVER_PLAYER_INFO,
    MSG_ACTION_TURN_HELM,
    MSG_ACTION_TURN_SAIL,
    MSG_GAME,
    MSG_ACK
} MsgType;

typedef enum {
    UNDEF,
    POSITIVE,
    NEGATIVE
} msgOrientation;

#define ORIENTATION_SF_CAST sf::Int8
#define TYPE_SF_CAST sf::Int16

class MessageData {
public:
    static MsgType popType(sf::Packet &packet);

public:
    MessageData();
    virtual ~MessageData();


    sf::Packet& toPacketWithoutType(sf::Packet &packet) const;
    sf::Packet& toPacketWithType(sf::Packet &packet) const;
    sf::Packet& fromPacketWithoutType(sf::Packet &packet);
    sf::Packet& fromPacketWithType(sf::Packet &packet);

public:
    virtual MsgType getType() const = 0;

protected:
    sf::Packet& putSfType(sf::Packet &packet) const;
    virtual void getDataFrom(sf::Packet &packet) = 0;
    virtual void putDataIn(sf::Packet &packet) const = 0;
};

#endif	/* MESSAGEDATA_H */

