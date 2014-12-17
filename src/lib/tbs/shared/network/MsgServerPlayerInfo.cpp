/* 
 * File:   MsgServerPlayerInfo.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 21:11
 */

#include "shared/network/MsgServerPlayerInfo.h"

MsgServerPlayerInfo::MsgServerPlayerInfo() {

}

MsgServerPlayerInfo::MsgServerPlayerInfo(unsigned int ID, unsigned short portRemote)
: m_ID(ID)
, m_portRemote(portRemote) {
}

MsgServerPlayerInfo::~MsgServerPlayerInfo() {
}

MsgType MsgServerPlayerInfo::getType() const {
    return MSG_SERVER_PLAYER_INFO;
}

void MsgServerPlayerInfo::getDataFrom(sf::Packet& packet) {
    sf::Uint32 sfID;
    sf::Uint16 sfPort;
    
    packet >> sfID >> sfPort;
    
    m_ID = static_cast<unsigned int>(sfID);
    m_portRemote =  static_cast<unsigned short>(sfPort);
}

void MsgServerPlayerInfo::putDataIn(sf::Packet& packet) const {
    packet << static_cast<sf::Uint32>(m_ID);
    packet << static_cast<sf::Uint16>(m_portRemote);
}

unsigned int MsgServerPlayerInfo::getID() const {
    return m_ID;
}

unsigned short MsgServerPlayerInfo::getServerPort() const {
    return m_portRemote;
}
