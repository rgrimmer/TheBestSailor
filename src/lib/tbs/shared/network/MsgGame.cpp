/* 
 * File:   MsgGame.cpp
 * Author: maxence
 * 
 * Created on 16 décembre 2014, 12:21
 */

#include "shared/network/MsgGame.h"
#include "shared/network/MsgTurnHelm.h"

MsgGame::MsgGame() {
}

MsgGame::~MsgGame() {
}

MsgType MsgGame::getType() const {
    return MsgType::MSG_GAME;
}

GameType MsgGame::getGameType() const {
    return GameType::GAME_UNDEF;
}


void MsgGame::getDataFrom(sf::Packet& packet) {

}

void MsgGame::putDataIn(sf::Packet& packet) const {

}
