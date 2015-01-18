/* 
 * File:   StateWaitGame.cpp
 * Author: maxence
 * 
 * Created on 16 janvier 2015, 23:28
 */
#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"

#include "client/state/game/StateWaitGame.h"

StateWaitGame::StateWaitGame(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player)
: State() {
}

StateWaitGame::~StateWaitGame() {
}

void StateWaitGame::Activate() {

}

void StateWaitGame::DeActivate() {

}

void StateWaitGame::Initialize() {

}

void StateWaitGame::Release() {

}

void StateWaitGame::Render(sf::RenderWindow& window) {

}

void StateWaitGame::Update(float dt) {

}

bool StateWaitGame::read(sf::Event& event) {
    return true;
}

bool StateWaitGame::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::Game:
//            return readMsgGame(msg);
            break;
    }
    return true;
}
