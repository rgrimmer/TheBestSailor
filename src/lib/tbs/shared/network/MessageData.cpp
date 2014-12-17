/* 
 * File:   MessageData.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 16:35
 */

#include <SFML/Config.hpp>

#include "shared/network/MessageData.h"

MessageData::MessageData() {
}

MessageData::~MessageData() {
}

MsgType MessageData::popType(sf::Packet& packet) {
    TYPE_SF_CAST sfType;
    packet >> sfType;
    return static_cast<MsgType>(sfType);
}

sf::Packet& MessageData::putSfType(sf::Packet& packet) const {
    auto sfType = static_cast<TYPE_SF_CAST>(getType());
    packet << sfType;
    return packet;
}

sf::Packet& MessageData::fromPacketWithType(sf::Packet& packet) {
    MessageData::popType(packet);
    getDataFrom(packet);
    return packet;
}

sf::Packet& MessageData::fromPacketWithoutType(sf::Packet& packet) {
    getDataFrom(packet);
    return packet;
}

sf::Packet& MessageData::toPacketWithType(sf::Packet& packet) const {
    putSfType(packet);
    putDataIn(packet);
    return packet;

}

sf::Packet& MessageData::toPacketWithoutType(sf::Packet& packet) const {
    putDataIn(packet);
    return packet;

}