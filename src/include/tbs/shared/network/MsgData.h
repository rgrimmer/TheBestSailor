/* 
 * File:   MsgData.h
 * Author: maxence
 *
 * Created on 11 décembre 2014, 16:35
 */

#ifndef MSGDATA_H
#define	MSGDATA_H
#include <iostream>
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Time.hpp>

#include "shared/network/MsgType.h"

class MsgData : public sf::Packet {
public:
    static bool checkValidity(const sf::Time& recvTime, sf::Time& localTime);


public:
    MsgData();
    MsgData(MsgType msgType);
    virtual ~MsgData();

    MsgType getMsgType() const;

protected:

    virtual void beforeOnSend(MsgData& message) {
        std::cout << "[Msg][OnSend] \t Send be default" << std::endl;
    }

    virtual void afterOnReceive(MsgData& message) {
        std::cout << "[Msg][OnReceive] \t Receive be default" << std::endl;
    }

private:
    //    void onReceive(const void* data, std::size_t size);
    //    virtual const void* onSend(std::size_t& size);


private:
    MsgType m_msgType;
};


#endif	/* MSGDATA_H */

