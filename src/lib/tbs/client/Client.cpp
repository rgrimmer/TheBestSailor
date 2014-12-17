/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */


#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "client/Client.h"
#include "client/game/ClientGame.h"
#include "client/game/ClientGameSpeedestWin.h"

#include "shared/Utils.h"
#include "shared/Kinematics.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MessageData.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/UtilsNetwork.h"
#include "shared/map/Map.h"


sf::View currentView;
sf::Vector2f posView(2000.0f, 2000.0f);
float zoomValue = 1.0f;
bool squared = true;

Client::Client()
: m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor")
, m_player(-1, "Unamed")
, m_game(nullptr) {
}

Client::~Client() {
}

const ClientNetwork& Client::getNetwork() const {
    return m_network;
}

void Client::start(const std::string & name) {
    m_player.setName(name);
    initConnectionWithServer();

    bool continued = false;
    do {
        initGame();
        continued = startGame();
    } while (continued);

}

void Client::initConnectionWithServer() {
    std::cout << "[NetW][Init]\tInitialize connection" << std::endl;
    m_network.connect();
    sendLocalPlayerInfo();
}

void Client::sendLocalPlayerInfo() {
    // @TODO
}

void Client::initGame() {
    // Wait receive map and send ack ready
    while (!m_game) {
        pollMessagesWait(sf::Time::Zero);
    }
}

bool Client::startGame() {
    return m_game->start();
}

void Client::pollMessages() {
    while (!m_network.getMessageQueue().empty()) {
        auto message = m_network.getMessageQueue().pop();
        read(message);
    }
}

bool Client::pollMessagesWait(sf::Time timeout) {
    if (m_network.getMessageQueue().empty())
        if (!m_network.getMessageQueue().waitEvent(timeout))
            return false;
    pollMessages();
    return true;
}

bool Client::read(MessageData* message) {

    switch (message->getType()) {
        case MsgType::MSG_GAME:
            read(dynamic_cast<MsgGame*> (message));
            break;
        case MsgType::MSG_SERVER_PLAYER_INFO:
            read(dynamic_cast<MsgServerPlayerInfo*> (message));
            break;
        default:
            return false;
    }
    return true;
}

bool Client::read(MsgGame* message) {
    switch (message->getGameType()) {
        case GameType::SPEEDEST_WIN:
            m_game = new ClientGameSpeedestWin(*this, m_window);
            break;
        default:
            std::cout << "Game Type Invalide" << std::endl;
            return false;
    }
    return true;
}

bool Client::read(MsgServerPlayerInfo* message) {
    m_network.getUdpManager().initialize("localhost", message->getServerPort());
    m_network.getUdpManager().startReceiverThread();
    return true;
}
