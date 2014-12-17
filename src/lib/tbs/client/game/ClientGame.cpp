/* 
 * File:   ClientGame.cpp
 * Author: maxence
 * 
 * Created on 17 décembre 2014, 16:50
 */

#include "client/game/ClientGame.h"

ClientGame::ClientGame() {
}

ClientGame::~ClientGame() {
}

bool ClientGame::start() {
    initGame();
    return startGameLoop();
}
