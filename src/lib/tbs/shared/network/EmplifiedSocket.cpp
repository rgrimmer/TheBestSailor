/* 
 * File:   EmplifiedSocket.cpp
 * Author: maxence
 * 
 * Created on 13 octobre 2014, 21:34
 */

#include "shared/network/EmplifiedSocket.h"
EmplifiedSocket::EmplifiedSocket() {
    
}

EmplifiedSocket::EmplifiedSocket(const sf::IpAddress &adress, unsigned short port) :
m_adress(adress), m_port(port) {
}

EmplifiedSocket::EmplifiedSocket(const EmplifiedSocket& orig) {
}

EmplifiedSocket::~EmplifiedSocket() {
}

