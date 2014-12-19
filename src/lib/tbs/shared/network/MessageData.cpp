/* 
 * File:   MessageData.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 16:35
 */
//#include <arpa/inet.h>
#include <iostream>
#include "shared/network/MessageData.h"

MessageData::MessageData(MsgType msgType)
: m_msgType(msgType) {
    (*this) << m_msgType;
}

MessageData::~MessageData() {
}

const void* MessageData::onSend(std::size_t& size) {
    std::cout << "[Send][Msg] \t Send Message " << static_cast<int> (getMsgType()) << std::endl;
    beforeOnSend(*this);
    size = getDataSize();
    return getData();
}

void MessageData::onReceive(const void* data, std::size_t size) {
    append(data, size);
    (*this) >> m_msgType;
    std::cout << "[Send][Msg] \t Receive Message " << static_cast<int> (getMsgType()) << std::endl;
    afterOnReceive(*this);
}

MsgType MessageData::getMsgType() const {
    return m_msgType;
}
