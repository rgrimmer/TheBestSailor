/* 
 * File:   ClientGame.cpp
 * Author: maxence
 * 
 * Created on 17 décembre 2014, 16:50
 */
#include <iostream>
#include "client/game/ClientGame.h"

ClientGame::ClientGame() {
}

ClientGame::~ClientGame() {
}

bool ClientGame::start() {
    std::cout << "[Client][Game][Init]" << std::endl;
    initGame();
    std::cout << "[Client][Game][Start]" << std::endl;
    return startGameLoop();
}
