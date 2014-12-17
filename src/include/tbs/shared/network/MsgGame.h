/* 
 * File:   MsgGame.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 12:21
 */

#ifndef MSGGAME_H
#define	MSGGAME_H

#include "shared/game/GameType.h"
#include "shared/network/MessageData.h"

class MsgGame : public MessageData {
public:
    MsgGame();
    virtual ~MsgGame();
    
    virtual MsgType getType() const;
    virtual GameType getGameType() const;

private:
    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;
};

#endif	/* MSGGAME_H */

