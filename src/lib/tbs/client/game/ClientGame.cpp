/* 
 * File:   ClientGame.cpp
 * Author: maxence
 * 
 * Created on 17 décembre 2014, 16:50
 */
#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>

#include "client/game/ClientGame.h"
#include "client/TextView.h"
#include "client/Client.h"

ClientGame::ClientGame(sf::RenderWindow& window, Client& client)
: m_window(window)
, m_client(client)
, m_updateTime(sf::seconds(1.0f / 60.0f))
, m_ping(sf::milliseconds(0))
, m_countFrames(0)
, m_lastCoutFrames(0)
, m_clockFPS()
, m_clockPing() {

}

ClientGame::~ClientGame() {
}

void ClientGame::start() {
    std::cout << "[Client][Game][Init]" << std::endl;
    init();
    sf::Clock clockGame, clockUpdate;
    std::cout << "[Client][Game][Start]" << std::endl;
    while (!isEnded() && m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            read(event);
        }

        sendInfo();
        m_clockPing.restart();

        m_client.pollMessages();

        update(clockUpdate.restart().asSeconds());
        displayView();
        calculateFPS();
    }
    std::cout << "[Client][Game][End]" << std::endl;
}

void ClientGame::displayView() {

    m_window.clear(sf::Color(5, 52, 79, 255));
    draw();

    TextView::setAbs(true);
    TextView::update();

    m_window.draw(TextView("PING(ms) : " + std::to_string(m_ping.asMilliseconds())));
    m_window.draw(TextView("FPS : " + std::to_string(m_lastCoutFrames)));
    m_window.display();
}

void ClientGame::calculateFPS() {
    if (m_clockFPS.getElapsedTime().asSeconds() >= 1) {
        m_lastCoutFrames = m_countFrames;
        m_countFrames = 0;
        m_clockFPS.restart();
    } else {
        ++m_countFrames;
    }
}

void ClientGame::setUpdateTime(const sf::Time& updateTime) {
    m_updateTime = updateTime;
}

