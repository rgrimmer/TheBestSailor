/* 
 * File:   GameStateWaitGame.cpp
 * Author: maxence
 * 
 * Created on 16 janvier 2015, 23:28
 */
#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"

#include "client/gamestate/GameStateWaitGame.h"

GameStateWaitGame::GameStateWaitGame(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player)
: GameState(window, network, player) {
}

GameStateWaitGame::~GameStateWaitGame() {
}

void GameStateWaitGame::Activate() {

}

void GameStateWaitGame::DeActivate() {

}

void GameStateWaitGame::Initialize() {

}

void GameStateWaitGame::Release() {

}

void GameStateWaitGame::Render(sf::RenderWindow& window) {

}

void GameStateWaitGame::Update(float dt) {

}

bool GameStateWaitGame::read(sf::Event& event) {
    return true;
}
bool GameStateWaitGame::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::Game:
//            return readMsgGame(msg);
            break;
    }
    return true;
}
