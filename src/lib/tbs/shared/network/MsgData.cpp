/* 
 * File:   MsgData.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 16:35
 */
//#include <arpa/inet.h>
#include <iostream>
#include "shared/network/MsgData.h"

MsgData::MsgData() {

}

MsgData::MsgData(MsgType msgType)
: m_msgType(msgType) {
    //    (*this) << m_msgType;
}

MsgData::~MsgData() {
}

bool MsgData::checkValidity(const sf::Time& recvTime, sf::Time& localTime) {
    if (recvTime < localTime)
        return false;

    localTime = recvTime;
    return true;
}

//const void* MsgData::onSend(std::size_t& size) {
//    std::cout << "[Send][Msg] \t Send Message " << static_cast<int> (getMsgType()) << ", size ("<<getDataSize() <<  ")"<< std::endl;
//    beforeOnSend(*this);
//    size = getDataSize();
//    return getData();
//}

//void MsgData::onReceive(const void* data, std::size_t size) {
//    clear();
//    append(data, size);
//    (*this) >> m_msgType;
//    afterOnReceive(*this);
//    std::cout << "[Send][Msg] \t Receive Message " << static_cast<int> (getMsgType()) << "size("<< getDataSize()<<")"<< std::endl;
//}

MsgType MsgData::getMsgType() const {
    return m_msgType;
}
