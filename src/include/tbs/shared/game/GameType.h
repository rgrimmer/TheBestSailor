/* 
 * File:   GameType.h
 * Author: maxence
 *
 * Created on 21 décembre 2014, 14:07
 */

#ifndef GAMETYPE_H
#define	GAMETYPE_H

#include <SFML/Config.hpp>
#include <SFML/Network/Packet.hpp>

enum class GameType : sf::Int8 {
    Undefined,
    SpeedestWin,

};

sf::Packet& operator>>(sf::Packet& packet, GameType& type);
sf::Packet& operator<<(sf::Packet& packet, GameType type);

#endif	/* GAMETYPE_H */

