/* 
 * File:   MsgServerPlayerInfo.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 21:11
 */

#include "shared/network/MsgServerPlayerInfo.h"

MsgServerPlayerInfo::MsgServerPlayerInfo()
: MessageData(MsgType::ServerPlayerInfo) {

}

MsgServerPlayerInfo::MsgServerPlayerInfo(MessageData& message) {
    afterOnReceive(message);
}

MsgServerPlayerInfo::MsgServerPlayerInfo(unsigned int ID, unsigned short portRemote)
: MessageData(MsgType::ServerPlayerInfo)
, m_ID(ID)
, m_portRemote(portRemote) {
}

MsgServerPlayerInfo::~MsgServerPlayerInfo() {
}

void MsgServerPlayerInfo::afterOnReceive(MessageData& message) {
    sf::Uint32 sfID;
    sf::Uint16 sfPort;
    if (message >> sfID >> sfPort) {
        m_ID = static_cast<unsigned int> (sfID);
        m_portRemote = static_cast<unsigned short> (sfPort);
    } else {
        std::cout << "Can't create message body" << std::endl;
    }

}

void MsgServerPlayerInfo::beforeOnSend(MessageData& message) {
    message << static_cast<sf::Uint32> (m_ID);
    message << static_cast<sf::Uint16> (m_portRemote);
}

unsigned int MsgServerPlayerInfo::getID() const {
    return m_ID;
} 

unsigned short MsgServerPlayerInfo::getServerPort() const {
    return m_portRemote;
}
