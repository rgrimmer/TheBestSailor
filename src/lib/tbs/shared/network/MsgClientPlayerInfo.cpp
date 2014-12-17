/* 
 * File:   MessageClientPlayerInfo.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 17:49
 */

#include "shared/network/MessageData.h"
#include "shared/network/MsgClientPlayerInfo.h"

sf::Packet& operator>>(sf::Packet& packet, MsgClientPlayerInfo& msg) {
    msg.fromPacketWithoutType(packet);
    return packet;
}

MsgClientPlayerInfo::MsgClientPlayerInfo()
: m_portUDP(0)
, m_name("") {
}

MsgClientPlayerInfo::MsgClientPlayerInfo(unsigned short PortUDP, const std::string& name)
: m_portUDP(PortUDP)
, m_name(name) {
}

MsgClientPlayerInfo::~MsgClientPlayerInfo() {
}

MsgType MsgClientPlayerInfo::getType() const {
    return MsgType::MSG_CLIENT_PLAYER_INFO;
}

void MsgClientPlayerInfo::getDataFrom(sf::Packet& packet) {
    sf::Uint16 sfPort;
    packet >> sfPort >> m_name;
    m_portUDP = static_cast<unsigned short> (sfPort);
}

void MsgClientPlayerInfo::putDataIn(sf::Packet& packet) const {
    packet << static_cast<sf::Uint16> (m_portUDP) << m_name;
}

const std::string& MsgClientPlayerInfo::getName() const {
    return m_name;
}

unsigned short MsgClientPlayerInfo::getPort() const {
    return m_portUDP;
}
