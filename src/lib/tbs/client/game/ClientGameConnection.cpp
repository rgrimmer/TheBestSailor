/* 
 * File:   ClientGameConnection.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 17:43
 */

#include <SFML/Network/Socket.hpp>
#include <SFML/Window/Event.hpp>

#include "shared/network/UtilsNetwork.h"
#include "client/game/ClientGameConnection.h"

ClientGameConnection::ClientGameConnection(sf::RenderWindow& window, Client& client)
: ClientGame(window, client)
, m_view(m_ipAddressInput) {

}

ClientGameConnection::~ClientGameConnection() {
}

unsigned short ClientGameConnection::getPort() const {
    return m_port;
}

sf::IpAddress ClientGameConnection::getIpAddress() const {
    return m_address;
}

void ClientGameConnection::init() {
    /*m_port = SERVER_PORT_TCP;
    m_address = sf::IpAddress::None;
    m_ipAddressInput = "localhost";
    m_window.setKeyRepeatEnabled(false);
    m_window.setJoystickThreshold(100.0f);*/
}

void ClientGameConnection::update(float dt) {

}

void ClientGameConnection::draw() {
    /*TextView::update();
    m_window.draw(m_view);*/
}

bool ClientGameConnection::read(MsgData& msg) {
    return false;
}

bool ClientGameConnection::read(sf::Event& event) {
   //DONE
    return false;
}

