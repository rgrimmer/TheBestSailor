/* 
 * File:   DrawShip.cpp
 * Author: maxence
 * 
 * Created on 29 novembre 2014, 10:43
 */

#include <SFML/Graphics/RenderTarget.hpp>

#include "client/ship/DrawShip.h"

DrawShip::DrawShip()
: m_shipView(sf::Vector2f(50.0f, 100.0f)) {
    m_shipView.setOrigin(25, 50);
    m_shipView.setFillColor(sf::Color::Red);

}

DrawShip::~DrawShip() {
    delete m_speedView;
}

void DrawShip::load(const Ship& ship) {
    m_ship = &ship;
    m_speedView = new VectorView<float>(m_ship->kinematics().speed(), "Vship");
    m_accView = new VectorView<float>(m_ship->kinematics().acceleration(), "", sf::Color::White);
}

void DrawShip::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.transform.translate(m_ship->kinematics().position());

    // Draw ship
    target.draw(m_shipView, states);

    // Draw sail
    target.draw(m_ship->sail(), states);

    // Draw vector
    target.draw(*m_speedView, states);
    // Draw vector
    target.draw(*m_accView, states);
}