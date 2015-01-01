/* 
 * File:   ClientGameConnection.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 17:43
 */

#include <SFML/Network/Socket.hpp>
#include <SFML/Window/Event.hpp>

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
    m_port = 0;
    m_address = sf::IpAddress::None;
    m_validate = false;
}

void ClientGameConnection::update(float dt) {

}

void ClientGameConnection::draw() {
    m_window.draw(m_view);
}

bool ClientGameConnection::isEnded() {
    return m_validate;
}

bool ClientGameConnection::read(MsgData& msg) {
    return false;
}

bool ClientGameConnection::read(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        char c = static_cast<char>(event.text.unicode);
        m_ipAddressInput.append(&c);
        return true;
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Return) {
            m_validate = true;
            return true;
        }
    }
    return false;
}

