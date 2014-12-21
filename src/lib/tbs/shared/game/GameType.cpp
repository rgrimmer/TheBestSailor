/* 
 * File:   GameType.cpp
 * Author: maxence
 * 
 * Created on 21 décembre 2014, 14:07
 */

#include "shared/game/GameType.h"

sf::Packet& operator>>(sf::Packet& packet, GameType& type) {
    typename std::underlying_type<GameType>::type sfType;
    packet >> sfType;
    type = static_cast<GameType> (sfType);
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, GameType type) {
    return packet << static_cast<std::underlying_type<GameType>::type> (type);
}