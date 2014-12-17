/* 
 * File:   MsgServerPlayerInfo.h
 * Author: maxence
 *
 * Created on 14 décembre 2014, 21:11
 */

#ifndef MSGSERVERPLAYERINFO_H
#define	MSGSERVERPLAYERINFO_H

#include <string>
#include <SFML/Network/IpAddress.hpp>

#include "MessageData.h"

class MsgServerPlayerInfo : public MessageData {
public:
    MsgServerPlayerInfo();
    MsgServerPlayerInfo(unsigned int ID, unsigned short portRemote);
    virtual ~MsgServerPlayerInfo();

    virtual MsgType getType() const;
    unsigned int getID() const;
    unsigned short getServerPort() const;


private:
    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;

private:
    unsigned int m_ID;
    unsigned short m_portRemote;

};

#endif	/* MSGSERVERPLAYERINFO_H */

