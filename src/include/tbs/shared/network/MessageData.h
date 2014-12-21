/* 
 * File:   MessageData.h
 * Author: maxence
 *
 * Created on 11 décembre 2014, 16:35
 */

#ifndef MESSAGEDATA_H
#define	MESSAGEDATA_H
#include <iostream>
#include "shared/network/MsgType.h"
#include <SFML/Network/Packet.hpp>

class MessageData : public sf::Packet {
public:
    MessageData();
    MessageData(MsgType msgType);
    virtual ~MessageData();

    MsgType getMsgType() const;

protected:

    virtual void beforeOnSend(MessageData& message) {
    std::cout << "[Msg][OnSend] \t Send be default" << std::endl;
    }

    virtual void afterOnReceive(MessageData& message) {
    std::cout << "[Msg][OnReceive] \t Receive be default" << std::endl;
    }

private:
//    void onReceive(const void* data, std::size_t size);
//    virtual const void* onSend(std::size_t& size);


private:
    MsgType m_msgType;
};


#endif	/* MESSAGEDATA_H */

