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
    m_port = SERVER_PORT_TCP;
    m_address = sf::IpAddress::None;
    m_validate = false;
    m_ipAddressInput = "localhost";
    m_window.setKeyRepeatEnabled(false);
    m_window.setJoystickThreshold(100.0f);
}

void ClientGameConnection::update(float dt) {

}

void ClientGameConnection::draw() {
    TextView::update();
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
        char c = static_cast<char> (event.text.unicode);
        std::cout << "Text entred(" << c << ")" << std::endl;
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.') {
            m_ipAddressInput.append(&c,1);
            return true;
        }
        return false;
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && m_ipAddressInput.size() > 0) {
            m_ipAddressInput.resize(m_ipAddressInput.size() - 1);
            return true;
        }
        if (event.key.code == sf::Keyboard::Return) {
            m_address = sf::IpAddress(m_ipAddressInput);
            m_validate = true;
            return true;
        }
    } else if (event.type == sf::Event::Closed) {
        m_window.close();
    }
    return false;
}

