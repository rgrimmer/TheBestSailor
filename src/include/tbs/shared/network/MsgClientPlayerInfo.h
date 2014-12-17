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
#include "MessageData.h"

class MsgClientPlayerInfo : public MessageData {
public:
    MsgClientPlayerInfo();
    MsgClientPlayerInfo(unsigned short PortUDP, const std::string &name);
    virtual ~MsgClientPlayerInfo();

    virtual MsgType getType() const;
    const std::string& getName() const; 
    unsigned short getPort() const;

private:
    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;


private:
    unsigned short m_portUDP;
    std::string m_name;

};

sf::Packet& operator >>(sf::Packet& packet, MsgClientPlayerInfo& msg);

#endif	/* MSGCLIENTPLAYERINFO_H */

