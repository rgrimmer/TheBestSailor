/* 
 * File:   GameWaitView.cpp
 * Author: maxence
 * 
 * Created on 22 janvier 2015, 13:00
 */

#include <iostream>

#include "client/view/menu/GameWaitView.h"

GameWaitView::GameWaitView()
: m_timeLeft(-1)
, m_prevTexture(-1) {

    // Set center text viewport
    m_centerSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});
    m_shipSfView.setViewport({0.0f, 0.5f, 1.0f, 1.0f});

    m_shapeShip.setPrimitiveType(sf::PrimitiveType::Quads);
    m_shapeShip.append(sf::Vertex({-100.0f, -100.0f}));
    m_shapeShip.append(sf::Vertex({100.0f, -100.0f}));
    m_shapeShip.append(sf::Vertex({100.0f, 100.0f}));
    m_shapeShip.append(sf::Vertex({-100.0f, 100.0f}));
    m_shapeShipRect = m_shapeShip.getBounds();

    setType(0);
}

GameWaitView::~GameWaitView() {
}

void GameWaitView::update(float dt) {
    decreaseTimeLeft(dt);
}

void GameWaitView::setTimeLeft(float timeLeft) {
    m_timeLeft = timeLeft;
    updateText();
}

void GameWaitView::decreaseTimeLeft(float dt) {
    m_timeLeft -= dt;
    updateText();

}

void GameWaitView::setType(int shipType) {
    if (m_prevTexture == shipType)
        return;

    m_prevTexture = shipType;
    std::string path = "share/tbs/textures/profile" + std::to_string(shipType) + ".png";

    std::cout << "set Texture !" << std::endl;
    if (!m_shipTexture.loadFromFile(path)) {
        if (m_shipTexture.loadFromFile("share/tbs/textures/profile1.png")) {

        }
    }

    sf::Vector2f sizeText = static_cast<sf::Vector2f> (m_shipTexture.getSize());
    m_shapeShip[0].texCoords = {0.0f, 0.0f};
    m_shapeShip[1].texCoords = {sizeText.x, 0.0f};
    m_shapeShip[2].texCoords = {sizeText.x, sizeText.y};
    m_shapeShip[3].texCoords = {0.0f, sizeText.y};
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
    TextView::setAbs(false);
    //
    //    // Draw left time
    target.setView(m_centerSfView);
    target.draw(TextView(m_leftTimeText, 60, Center), states);

    sf::Vector2f sizeW = static_cast<sf::Vector2f> (target.getSize());
    target.setView(sf::View({0.0f, 0.0f, sizeW.x, sizeW.y}));
    sf::Vector2f shipPos;
    shipPos.x = sizeW.x / 2;
    shipPos.y = (sizeW.y) / 2 + 20.0f;
    //    
    //    target.setView(m_shipSfView);
    //    std::string size = "widh(" + std::to_string(m_shipTexture.getSize().x) + "), height(" + std::to_string(m_shipTexture.getSize().y) + ")";
    //        target.draw(TextView(size, 60, Center), states);
    states.transform.translate(shipPos);
    states.texture = &m_shipTexture;
    target.draw(m_shapeShip, states);

    target.setView(currentView);
}

