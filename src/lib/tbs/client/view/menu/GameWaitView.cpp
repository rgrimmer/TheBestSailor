/* 
 * File:   GameWaitView.cpp
 * Author: maxence
 * 
 * Created on 22 janvier 2015, 13:00
 */

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "client/view/menu/GameWaitView.h"

GameWaitView::GameWaitView()
: m_timeLeft(-1) {

    // Set center text viewport
    m_centerSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});
    m_shipSfView.setViewport({0.0f, 0.5f, 1.0f, 1.0f});

    m_shipSprite.setTexture(m_shipTexture);
    setTexture(0);
    //    m_shipSprite.setScale(200.0f /m_shipTexture.getSize().x, 200.0f /m_shipTexture.getSize().y);
}

GameWaitView::~GameWaitView() {
}

void GameWaitView::setTimeLeft(float timeLeft) {
    m_timeLeft = timeLeft;
    updateText();
}

void GameWaitView::decreaseTimeLeft(float dt) {
    m_timeLeft -= dt;
    updateText();

}

void GameWaitView::setTexture(int shipType) {
    m_prevTexture = shipType;
    std::string path = "share/tbs/textures/boat" + std::to_string(shipType) + ".png";

    std::cout << "set Texture !" << std::endl;
    if (!m_shipTexture.loadFromFile(path)) {
        if (m_shipTexture.loadFromFile("share/tbs/textures/boat.png"))
            std::cout << "Texture load !!!!!!!" << std::endl;
    } else {
        std::cout << "Texture load !!!!!!!" << std::endl;
    }
    m_shipSprite.setTexture(m_shipTexture, true);
}

void GameWaitView::updateText() {
    if (m_timeLeft >= 0) {
        m_leftTimeText = "Game start in " + std::to_string(static_cast<int> (m_timeLeft));
    } else {
        m_leftTimeText = "Please Wait. A game is already start";
    }
}

void GameWaitView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    MenuView::draw(target, states);

    sf::View currentView = target.getView();
    //
    //    TextView::setAbs(false);
    //
    //    // Draw left time
        target.setView(m_centerSfView);
        target.draw(TextView(m_leftTimeText, 60, Center), states);
    //    
    //    target.setView(m_shipSfView);
//    std::string size = "widh(" + std::to_string(m_shipTexture.getSize().x) + "), height(" + std::to_string(m_shipTexture.getSize().y) + ")";
//        target.draw(TextView(size, 60, Center), states);
//    target.draw(sf::RectangleShape({m_shipSprite.getGlobalBounds().width, m_shipSprite.getGlobalBounds().height}), states);

    target.setView(currentView);
}

