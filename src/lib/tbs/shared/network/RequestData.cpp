/* 
 * File:   RequestData.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 16:35
 */

#include <SFML/Config.hpp>

#include "shared/network/RequestData.h"

#define TYPE_SF_CAST sf::Int16
RequestData::RequestData() {
}

RequestData::~RequestData() {
}

reqType RequestData::popType(sf::Packet& packet) {
    TYPE_SF_CAST sfType;
    packet >> sfType;
    return static_cast<reqType>(sfType);
}

sf::Packet& RequestData::putSfType(sf::Packet& packet) const {
    auto sfType = static_cast<TYPE_SF_CAST>(getType());
    packet << sfType;
    return packet;
}

sf::Packet& RequestData::fromPacketWithType(sf::Packet& packet) {
    RequestData::popType(packet);
    getDataFrom(packet);
    return packet;
}

sf::Packet& RequestData::fromPacketWithoutType(sf::Packet& packet) {
    getDataFrom(packet);
    return packet;
}

sf::Packet& RequestData::toPacketWithType(sf::Packet& packet) const {
    putSfType(packet);
    putDataIn(packet);
    return packet;

}

sf::Packet& RequestData::toPacketWithoutType(sf::Packet& packet) const {
    putDataIn(packet);
    return packet;

}