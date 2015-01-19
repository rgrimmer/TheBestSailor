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

#include "shared/network/MsgData.h"

#include "client/Client.h"
#include "client/TextView.h"

Client::Client()
: m_player(-1, "Unamed")
, m_state(m_network, m_player) {
}

Client::~Client() {
}

void Client::start(const std::string & name) {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    m_window.create(sf::VideoMode(800, 600), "The Best Sailor", sf::Style::Default, settings);
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_window.setJoystickThreshold(100.0f);

    m_player.setName(name);
    m_state.initialize();

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {

            if (!m_state.read(event)) {
                m_window.close();
            }
        }

        pollMessages();

        m_state.update(m_clock.restart().asSeconds());
        m_window.clear(sf::Color(5, 52, 79, 255));
        m_state.render(m_window);

        TextView::setAbs(true);
        TextView::update();

        m_window.display();
    }
    
    m_state.release();
}

void Client::pollMessages() {
    while (!m_network.getMessageQueue().empty()) {
        auto message = m_network.getMessageQueue().pop();
        m_state.read(*message);
        delete message;
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

