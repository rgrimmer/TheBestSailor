/* 
 * File:   MsgType.h
 * Author: maxence
 *
 * Created on 17 décembre 2014, 23:47
 */

#ifndef EMSGTYPE_H
#define	EMSGTYPE_H

#include <SFML/Config.hpp>
#include <SFML/Network/Packet.hpp>

enum class MsgType : sf::Int16 {
    Undef,
    Disconnect,
    ClientPlayerInfo,
    ServerPlayerInfo,
    Action,
    Game,
    GameInfo,
    Acknowledgment
};

enum class MsgOrientation : sf::Int8 {
    UNDEF,
    Positive,
    Negative
};

sf::Packet& operator>>(sf::Packet& packet, MsgType& en);
sf::Packet& operator<<(sf::Packet& packet, MsgType en);
sf::Packet& operator>>(sf::Packet& packet, MsgOrientation& en);
sf::Packet& operator<<(sf::Packet& packet, MsgOrientation en);

#endif	/* MSGTYPE_H */

