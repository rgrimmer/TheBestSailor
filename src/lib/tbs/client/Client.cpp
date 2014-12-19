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
#include "shared/network/MsgClientPlayerInfo.h"
#include "client/ClientWorld.h"

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
    std::cout << "[NetW][InitCWS]\tInitialize connection" << std::endl;
    m_network.connect();
    m_network.getTcpManager().startReceiverThread();
    sendLocalPlayerInfo();
    waitServerPlayerInfo();
}

void Client::sendLocalPlayerInfo() {
    std::cout << "[Client][SendLPI] \t Envoi des informations du joueurs" << std::endl;
    MsgClientPlayerInfo msg(m_network.getUdpManager().getPort(), m_player.getName());
    m_network.getTcpManager().send(msg);
}

void Client::waitServerPlayerInfo() {
    std::cout << "[Client][WSPI] \t Attente des infos du serveur" << std::endl;
    pollMessagesWait(sf::Time::Zero);
}

void Client::initGame() {
    std::cout << "[Client][InitG] \t Initialization of the game started" << std::endl;
    // Wait receive map and send ack ready
    while (!m_game) {
        pollMessagesWait(sf::Time::Zero);
    }
}

bool Client::startGame() {
    return m_game->start();
}

void Client::pollMessages() {
    std::cout << "[Client][PoolM] \t start to pull messages" << std::endl;
    while (!m_network.getMessageQueue().empty()) {
        auto message = m_network.getMessageQueue().pop();
        read(*message);
    }
}

bool Client::pollMessagesWait(sf::Time timeout) {
    if (m_network.getMessageQueue().empty()) {
        std::cout << "[Client][PoolM][Wait]" << std::endl;
        if (!m_network.getMessageQueue().waitEvent(timeout)) {
            std::cout << "[Client][PoolM][Wait] \t timeout" << std::endl;
            return false;
        }
    }
    pollMessages();
    return true;
}

bool Client::read(MsgGame& message) {
    std::cout << "[Client][Read] \t Read Game Message" << std::endl;
    ClientWorld world;
    sf::Int32 width, height, seedHeight, seedWind;
    message >> width >> height >> seedHeight >> seedWind;
    std::cout << "RECEIVE map(" << width << ", " << height<< ", " <<seedHeight<< ", " <<seedWind<< ")" << std::endl;
    world.initializeMap(width, height, seedHeight, seedWind);
    world.initialize();
    auto *gameSpeedest = new ClientGameSpeedestWin(*this, m_window);
    gameSpeedest->setClientWorld(world);
    m_game = gameSpeedest;
//    switch (message.getGameType()) { // @TODO
//        case GameType::SPEEDEST_WIN:
//        {
//            auto CGSW = new ClientGameSpeedestWin(*this, m_window);
//            message >> *CGSW;
//            m_game = CGSW;
//        }
//            break;
//        default:
//            std::cout << "Game Type Invalide" << std::endl;
//            return false;
//    }
    return true;
}

bool Client::read(MessageData& message) {
    std::cout << "[Client][Read] \t Read Default Message" << std::endl;
    switch (message.getMsgType()) {
        case MsgType::Game:
        {
            m_game = new ClientGameSpeedestWin(*this, m_window);
            auto tmp = static_cast<MsgGame> (message);
            read(tmp);
        }
            break;
        case MsgType::ServerPlayerInfo:
        {
            auto tmp = static_cast<MsgServerPlayerInfo> (message);
            read(tmp);
        }
            break;
        default:
            return false;
    }
    return true;
}

bool Client::read(MsgServerPlayerInfo& message) {
    std::cout << "[Client][Read] \t Read Server Player Info Message" << std::endl;
    m_network.getUdpManager().initialize("localhost", SERVER_PORT_UDP/*message->getServerPort()*/); // @TODO
    m_network.getUdpManager().startReceiverThread();
    return true;
}
