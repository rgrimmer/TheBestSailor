/* 
 * File:   MsgGame.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 12:21
 */

#ifndef MSGGAME_H
#define	MSGGAME_H

#include "shared/game/GameType.h"
#include "shared/network/MsgData.h"

class MsgGame : public MsgData {
public:
    MsgGame();
    MsgGame(MsgData &message);
    
    GameType getGameType() const { return GameType::SpeedestWin; } // @TODO
    virtual ~MsgGame();
};

#endif	/* MSGGAME_H */

