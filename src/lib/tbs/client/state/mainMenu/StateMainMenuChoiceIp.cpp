/* 
 * File:   StateMainMenuChoiceIp.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 11:06
 */

#include "client/state/mainMenu/StateMainMenuChoiceIp.h"
#include "shared/network/MsgData.h"

StateMainMenuChoiceIp::StateMainMenuChoiceIp(MainMenuStateManager& manager, std::string& address)
: m_manager(manager)
, m_address(address)
, m_choiceIpView(address) {
}

StateMainMenuChoiceIp::~StateMainMenuChoiceIp() {
}

void StateMainMenuChoiceIp::initialize() {
}

void StateMainMenuChoiceIp::release() {
}

void StateMainMenuChoiceIp::activate() {
}

void StateMainMenuChoiceIp::deactivate() {
}

void StateMainMenuChoiceIp::update(float dt) {
}

void StateMainMenuChoiceIp::render(sf::RenderWindow& window) const {
    window.draw(m_choiceIpView);
}

bool StateMainMenuChoiceIp::read(sf::Event& event) {
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

bool StateMainMenuChoiceIp::read(MsgData& msg) {
    return true;
}
