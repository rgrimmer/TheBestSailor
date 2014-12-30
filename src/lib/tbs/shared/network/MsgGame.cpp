/* 
 * File:   MsgGame.cpp
 * Author: maxence
 * 
 * Created on 16 décembre 2014, 12:21
 */

#include "shared/network/MsgGame.h"

MsgGame::MsgGame()
: MsgData(MsgType::Game) {
}

MsgGame::MsgGame(MsgData& message)
: MsgData(MsgType::Game) {
    this->append(message.getData(), message.getDataSize());
    sf::Int32 r;
    *this >> r;
}

MsgGame::~MsgGame() {
}
