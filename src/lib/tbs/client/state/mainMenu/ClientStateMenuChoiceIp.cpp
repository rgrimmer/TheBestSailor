/* 
 * File:   ClientStateMenuChoiceIp.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 11:06
 */

#include "client/state/mainMenu/ClientStateMenuChoiceIp.h"
#include "shared/network/MsgData.h"

ClientStateMenuChoiceIp::ClientStateMenuChoiceIp(ClientStateMenu& manager, std::string& address)
: m_manager(manager)
, m_address(address)
, m_choiceIpView(address) {
}

ClientStateMenuChoiceIp::~ClientStateMenuChoiceIp() {
}

void ClientStateMenuChoiceIp::initialize() {
}

void ClientStateMenuChoiceIp::release() {
}

void ClientStateMenuChoiceIp::activate() {
}

void ClientStateMenuChoiceIp::deactivate() {
}

void ClientStateMenuChoiceIp::update(float dt) {
}

void ClientStateMenuChoiceIp::render(sf::RenderWindow& window) const {
    window.draw(m_choiceIpView);
}

bool ClientStateMenuChoiceIp::read(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        char c = static_cast<char> (event.text.unicode);
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.') {
            m_address.append(&c, 1);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && m_address.size() > 0) {
            m_address.erase(m_address.size() - 1, 1);
        }
        else if (event.key.code == sf::Keyboard::Return) {
            m_manager.push(EMainMenuState::SendInfo);
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            m_manager.pop();
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    }

    return true;
}

bool ClientStateMenuChoiceIp::read(MsgData& msg) {
    return true;
}
