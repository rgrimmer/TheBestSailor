/* 
 * File:   ClientGame.h
 * Author: maxence
 *
 * Created on 17 décembre 2014, 16:50
 */

#ifndef CLIENTGAME_H
#define	CLIENTGAME_H

class MessageData;

class ClientGame {
public:
    ClientGame();
    virtual ~ClientGame();

    bool start();
    virtual bool readInitGame(MessageData& msg) = 0;

protected:
    virtual void initGame() = 0;
    virtual bool startGameLoop() = 0;

};

#endif	/* CLIENTGAME_H */

