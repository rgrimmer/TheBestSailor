/* 
 * File:   ClientStateMenuExchangeInfo.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 11:28
 */
#include <iostream>

#include "shared/network/UtilsNetwork.h"
#include "shared/network/MsgData.h"

#include "client/ClientPlayer.h"
#include "client/network/ClientNetwork.h"

#include "client/state/ClientState.h"
#include "client/state/mainMenu/ClientStateMenu.h"
#include "client/state/mainMenu/ClientStateMenuExchangeInfo.h"

ClientStateMenuExchangeInfo::ClientStateMenuExchangeInfo(ClientStateMenu& manager, ClientNetwork& network, ClientPlayer& player, std::string& address)
: m_manager(manager)
, m_network(network)
, m_player(player)
, m_stdAddress(address)
, m_address()
, m_connectionView() {

}

ClientStateMenuExchangeInfo::~ClientStateMenuExchangeInfo() {
}

void ClientStateMenuExchangeInfo::initialize(void) {
}

void ClientStateMenuExchangeInfo::release(void) {
}

void ClientStateMenuExchangeInfo::activate(void) {
    auto separator = m_stdAddress.find(":");
    if(separator == std::string::npos) {
        m_port = SERVER_PORT_TCP;
        m_address = m_stdAddress;
    } else {
        m_port = atoi(m_stdAddress.substr(separator + 1).c_str());
        m_address = m_stdAddress.substr(0, separator);
    }
    m_connectionView.setAdressText(m_address.toString());
}

void ClientStateMenuExchangeInfo::deactivate(void) {
}

void ClientStateMenuExchangeInfo::update(float dt) {
    if (m_network.connect(m_address, m_port, sf::milliseconds(1000)))
        initConnectionWithServer();
}

void ClientStateMenuExchangeInfo::render(sf::RenderWindow& window) const {
    window.draw(m_connectionView);
}

void ClientStateMenuExchangeInfo::initConnectionWithServer(void) {
    std::cout << "[NetW][InitCWS]\tInitialize connection" << std::endl;
    m_network.getTcpManager().startReceiverThread();
    sendLocalPlayerInfo();
}

void ClientStateMenuExchangeInfo::sendLocalPlayerInfo(void) {
    std::cout << "[Client][SendLPI] \t Envoi des informations du joueurs" << std::endl;
    MsgData msg;
    msg << MsgType::ClientPlayerInfo << static_cast<sf::Uint16> (m_network.getUdpManager().getPort()) << m_player.getName();
    m_network.getTcpManager().send(msg);
    std::cout << "[Client][SendLPI] \t Send : name(" << m_player.getName() << ") port(" << m_network.getUdpManager().getPort() << ")" << std::endl;
}

bool ClientStateMenuExchangeInfo::read(sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                m_manager.pop();
                break;
            default:
                break;
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    } else if (event.type == sf::Event::MouseButtonPressed) {
        std::cout << "posInWindow(" << event.mouseButton.x << " " << event.mouseButton.y << ")" << std::endl;
    }

    return true;
}

bool ClientStateMenuExchangeInfo::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::ServerPlayerInfo:
            return readMsgServerPlayerInfo(msg);

        default:
            return true;
    }
}

bool ClientStateMenuExchangeInfo::readMsgServerPlayerInfo(MsgData &message) {
    sf::Uint16 udpPort, id;
    message >> udpPort >> id;
    std::cout << "[Client][Read] \t Read Server Player Info Message. id(" << id << "), serverUdpPort(" << udpPort << ")" << std::endl;
    m_player.setId(id);
    m_network.getUdpManager().initialize(m_address, udpPort);
    m_network.getUdpManager().startReceiverThread();
    m_manager.getManager().push(EClientState::Game);
    return false;
}
