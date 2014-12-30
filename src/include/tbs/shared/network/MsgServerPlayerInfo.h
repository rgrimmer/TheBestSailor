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

#include "MsgData.h"

class MsgServerPlayerInfo : public MsgData {
public:
    MsgServerPlayerInfo();
    MsgServerPlayerInfo(MsgData& message);
    MsgServerPlayerInfo(unsigned int ID, unsigned short portRemote);
    virtual ~MsgServerPlayerInfo();
    
        unsigned int getID() const;
    unsigned short getServerPort() const;
    
private:
    virtual void beforeOnSend(MsgData& message);
    virtual void afterOnReceive(MsgData& message);

private:
    unsigned int m_ID;
    unsigned short m_portRemote;

};

#endif	/* MSGSERVERPLAYERINFO_H */

