/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "client/Client.h"
#include "client/game/ClientGame.h"
#include "client/game/ClientGameSpeedestWin.h"

#include "shared/Utils.h"
#include "shared/Kinematics.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MsgData.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/UtilsNetwork.h"
#include "shared/map/Map.h"
#include "shared/network/MsgClientPlayerInfo.h"
#include "client/ClientWorld.h"
#include "client/game/ClientGameConnection.h"

Client::Client()
: m_player(-1, "Unamed")
, m_game(nullptr) {
}

Client::~Client() {
}

const ClientNetwork& Client::getNetwork() const {
    return m_network;
}

ClientNetwork& Client::getNetwork() {
    return m_network;
}

void Client::start(const std::string & name) {
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    m_window.create(sf::VideoMode(800, 600), "The Best Sailor", sf::Style::Default, settings);
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_window.setJoystickThreshold(100.0f);

    g_gameStateManager.Initialize(m_window, m_network, m_player);
    
    while (m_window.isOpen()) {
        g_gameStateManager.UpdateAndRender(m_window, m_clock.restart().asSeconds());
    }
    
    g_gameStateManager.Release();
    
    /*m_player.setName(name);

    
    m_connection = new ClientGameConnection(m_window, *this);
    m_connection->start();
    if (!m_window.isOpen())
        return;
    std::cout << "TRY TO CONNECT TO " << m_connection->getIpAddress().toString() << std::endl;
    initConnectionWithServer(m_connection->getIpAddress());
    while (m_window.isOpen()) {
        initGame();
        startGame();
    }
    doDisconnection();*/
}

void Client::initConnectionWithServer(const sf::IpAddress &address) {
    std::cout << "[NetW][InitCWS]\tInitialize connection" << std::endl;
    m_network.connect(address);
    m_network.getTcpManager().startReceiverThread();
    sendLocalPlayerInfo();
    waitServerPlayerInfo();
}

void Client::sendLocalPlayerInfo() {
    std::cout << "[Client][SendLPI] \t Envoi des informations du joueurs" << std::endl;
    MsgData msg;
    msg << MsgType::ClientPlayerInfo << static_cast<sf::Uint16> (m_network.getUdpManager().getPort()) << m_player.getName();
    m_network.getTcpManager().send(msg);
    std::cout << "[Client][SendLPI] \t Send : name(" << m_player.getName() << ") port(" << m_network.getUdpManager().getPort() << ")" << std::endl;
}

void Client::waitServerPlayerInfo() {
    std::cout << "[Client][WSPI] \t Wait information from server" << std::endl;
    pollMessagesWait(sf::Time::Zero);
}

void Client::initGame() {
    std::cout << "[Client][InitG] \t Initialization of the game started" << std::endl;
    // Wait receive map and send ack ready
    while (!m_game) {
        pollMessagesWait(sf::Time::Zero);
    }
}

void Client::startGame() {
    m_game->start();
    m_game = nullptr;
}

void Client::doDisconnection() {
    m_network.getTcpManager().disconnect();
}

void Client::pollMessages() {
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

bool Client::read(MsgData& message) {
    MsgData msgCopy(message);
    MsgType msgType;
    message >> msgType;
    switch (msgType) {
        case MsgType::Game:
            return readMsgGame(message);
        case MsgType::ServerPlayerInfo:
            return readMsgServerPlayerInfo(message);
        default:
            if (m_game)
                if (m_game->read(msgCopy))
                    return true;
            std::cout << "[Client][Read] \t UnReadable Message(" << static_cast<int> (msgType) << ")" << std::endl;
            return false;
    }
    return true;
}

bool Client::readMsgServerPlayerInfo(MsgData &message) {
    sf::Uint16 udpPort, id;
    message >> udpPort >> id;
    std::cout << "[Client][Read] \t Read Server Player Info Message. id(" << id << "), serverUdpPort(" << udpPort << ")" << std::endl;
    m_player.setId(id);
    m_network.getUdpManager().initialize(m_connection->getIpAddress(), udpPort); // @TODO
    m_network.getUdpManager().startReceiverThread();
    return true;
}

bool Client::readMsgGame(MsgData& message) {
    std::cout << "[Client][Read] \t Read Game Message" << std::endl;
    GameType gameType;
    message >> gameType;
    switch (gameType) {
        case GameType::SpeedestWin:
        {
            m_game = new ClientGameSpeedestWin(m_window, *this, m_player);
            m_game->readInitGame(message);
            return true;
        }
        default:
            std::cout << "Game Type Invalide" << std::endl;
            return false;
    }
    return true;
}

