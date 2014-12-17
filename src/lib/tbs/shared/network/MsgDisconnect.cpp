/* 
 * File:   MsgDisconnect.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 21:28
 */

#include "shared/network/MsgDisconnect.h"

MsgDisconnect::MsgDisconnect() {
}

MsgDisconnect::~MsgDisconnect() {
}

MsgType MsgDisconnect::getType() const {
    return MsgType::MSG_DISCONNECT;
}

void MsgDisconnect::getDataFrom(sf::Packet& packet) {

}

void MsgDisconnect::putDataIn(sf::Packet& packet) const {

}
