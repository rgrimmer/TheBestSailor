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
    MsgGame(MessageData &message);
    
    GameType getGameType() const { return GameType::SpeedestWin; } // @TODO
    virtual ~MsgGame();
};

#endif	/* MSGGAME_H */

