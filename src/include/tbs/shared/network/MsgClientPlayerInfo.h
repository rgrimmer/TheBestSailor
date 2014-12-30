/* 
 * File:   MsgClientPlayerInfo.h
 * Author: maxence
 *
 * Created on 14 décembre 2014, 17:49
 */

#ifndef MSGCLIENTPLAYERINFO_H
#define	MSGCLIENTPLAYERINFO_H

#include <string>
#include <SFML/Network/Packet.hpp>
#include "MsgData.h"

class MsgClientPlayerInfo : public MsgData {
public:
    MsgClientPlayerInfo();
    MsgClientPlayerInfo(MsgData &message);
    MsgClientPlayerInfo(unsigned short portUDP, const std::string &name);
    virtual ~MsgClientPlayerInfo();

    const std::string& getName();
    unsigned short getPort();

    virtual void afterOnReceive(MsgData& message);
    virtual void beforeOnSend(MsgData& message);

private:
    unsigned short m_portUDP;
    std::string m_name;
};

//class MsgObjClientPlayerInfo {
//    
//    const std::string& getName() const; 
//    unsigned short getPort() const;
//};
//
//void operator>>(MsgClientPlayerInfo &msg, MsgObjClientPlayerInfo& obj);

#endif	/* MSGCLIENTPLAYERINFO_H */

