/* 
 * File:   RequestDisconnect.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 21:28
 */

#include "shared/network/RequestDisconnect.h"

RequestDisconnect::RequestDisconnect() {
}

RequestDisconnect::~RequestDisconnect() {
}

reqType RequestDisconnect::getType() const {
    return reqType::REQ_DISCONNECT;
}

void RequestDisconnect::getDataFrom(sf::Packet& packet) {

}

void RequestDisconnect::putDataIn(sf::Packet& packet) const {

}
