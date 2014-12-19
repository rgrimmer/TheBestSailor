/* 
 * File:   MessageClientPlayerInfo.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 17:49
 */
#include <iostream>

#include "shared/network/MessageData.h"
#include "shared/network/MsgClientPlayerInfo.h"

MsgClientPlayerInfo::MsgClientPlayerInfo()
: MessageData(MsgType::ClientPlayerInfo)
, m_portUDP(0)
, m_name("") {

}

MsgClientPlayerInfo::MsgClientPlayerInfo(MessageData& message)
: MessageData(MsgType::ClientPlayerInfo) {
    sf::Uint16 sfPort;
    message >> sfPort >> m_name;
    m_portUDP = static_cast<unsigned short> (sfPort);
    std::cout << "[Msg][OnReceive] \t Receive name(" << m_name << ") port(" << m_portUDP << ")" << std::endl;
}


MsgClientPlayerInfo::MsgClientPlayerInfo(unsigned short portUDP, const std::string& name)
: MessageData(MsgType::ClientPlayerInfo)
, m_portUDP(portUDP)
, m_name(name) {
}

void MsgClientPlayerInfo::beforeOnSend() {
    (*this) << static_cast<sf::Uint16> (m_portUDP) << m_name;
    std::cout << "[Msg][OnSend] \t Send name(" << m_name << ") port(" << m_portUDP << ")" << std::endl;
}

void MsgClientPlayerInfo::afterOnReceive() {
    sf::Uint16 sfPort;
    (*this) >> sfPort >> m_name;
    m_portUDP = static_cast<unsigned short> (sfPort);
    std::cout << "[Msg][OnReceive] \t Receive name(" << m_name << ") port(" << m_portUDP << ")" << std::endl;
}

MsgClientPlayerInfo::~MsgClientPlayerInfo() {
}

const std::string& MsgClientPlayerInfo::getName() {
    return m_name;
    //    return *static_cast<const std::string*> (static_cast<const void*> (&(static_cast<const unsigned short*> (getData())[1])));
}

unsigned short MsgClientPlayerInfo::getPort() {
    return m_portUDP;
    //    return static_cast<const unsigned short*> (this->getData())[0];
}
