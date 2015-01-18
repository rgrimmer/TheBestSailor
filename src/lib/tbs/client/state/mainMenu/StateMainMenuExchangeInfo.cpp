/* 
 * File:   StateMainMenuExchangeInfo.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 11:28
 */

#include "shared/network/MsgData.h"

#include "client/ClientPlayer.h"
#include "client/network/ClientNetwork.h"

#include "client/state/ClientState.h"
#include "client/state/mainMenu/MainMenuStateManager.h"
#include "client/state/mainMenu/StateMainMenuExchangeInfo.h"
#include "client/state/mainMenu/StateMainMenu.h"


StateMainMenuExchangeInfo::StateMainMenuExchangeInfo(MainMenuStateManager& manager, ClientNetwork& network, ClientPlayer& player, std::string& address)
: m_manager(manager)
, m_network(network)
, m_player(player)
, m_address(address)
, m_connectionView(address) {

}

StateMainMenuExchangeInfo::~StateMainMenuExchangeInfo() {
}

void StateMainMenuExchangeInfo::initialize(void) {
}

void StateMainMenuExchangeInfo::release(void) {
}

void StateMainMenuExchangeInfo::activate(void) {
}

void StateMainMenuExchangeInfo::deactivate(void) {
}

void StateMainMenuExchangeInfo::update(float dt) {
    if(m_network.connect(m_address, sf::milliseconds(1000)))
        initConnectionWithServer(m_address);
}

void StateMainMenuExchangeInfo::render(sf::RenderWindow& window) const {
    window.draw(m_connectionView);
}

void StateMainMenuExchangeInfo::initConnectionWithServer(const sf::IpAddress &address) {
    std::cout << "[NetW][InitCWS]\tInitialize connection" << std::endl;
    m_network.getTcpManager().startReceiverThread();
    sendLocalPlayerInfo();
}

void StateMainMenuExchangeInfo::sendLocalPlayerInfo() {
    std::cout << "[Client][SendLPI] \t Envoi des informations du joueurs" << std::endl;
    MsgData msg;
    msg << MsgType::ClientPlayerInfo << static_cast<sf::Uint16> (m_network.getUdpManager().getPort()) << m_player.getName();
    m_network.getTcpManager().send(msg);
    std::cout << "[Client][SendLPI] \t Send : name(" << m_player.getName() << ") port(" << m_network.getUdpManager().getPort() << ")" << std::endl;
}

bool StateMainMenuExchangeInfo::read(sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            m_manager.pop();
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    }

    return true;
}

bool StateMainMenuExchangeInfo::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::ServerPlayerInfo:
            return readMsgServerPlayerInfo(msg);

        default:
            return true;
    }
}

bool StateMainMenuExchangeInfo::readMsgServerPlayerInfo(MsgData &message) {
    sf::Uint16 udpPort, id;
    message >> udpPort >> id;
    std::cout << "[Client][Read] \t Read Server Player Info Message. id(" << id << "), serverUdpPort(" << udpPort << ")" << std::endl;
    m_player.setId(id);
    m_network.getUdpManager().initialize(m_address, udpPort);
    m_network.getUdpManager().startReceiverThread();
    m_manager.getManager().push(EClientState::Game);
    return false;
}
