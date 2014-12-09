/* 
 * File:   DrawShip.cpp
 * Author: maxence
 * 
 * Created on 29 novembre 2014, 10:43
 */

#include <SFML/Graphics/RenderTarget.hpp>

#include "client/ship/ShipView.h"

ShipView::ShipView(const Ship &ship)
: m_ship(ship)
, m_shipShap(sf::Vector2f(50.0f, 100.0f)) {
    m_speedView = new VectorView<float>(m_ship.kinematics().speed(), "Vship");
    m_accView = new VectorView<float>(m_ship.kinematics().acceleration(), "", sf::Color::White);
    
    m_shipShap.setOrigin(25.0f, 50.0f);
    m_shipShap.setFillColor(sf::Color::Red);

}

ShipView::~ShipView() {
    delete m_speedView;
}

void ShipView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.transform.rotate(m_ship.kinematics().direction(), m_ship.kinematics().position());
    states.transform.translate(m_ship.kinematics().position());

    // Draw ship
    target.draw(m_shipShap, states);

    // Draw sail
    target.draw(m_ship.sail(), states);
    
    // Draw vector
    target.draw(*m_speedView, states);
    // Draw vector
    target.draw(*m_accView, states);
    
    // Draw helm
        states.transform.translate(sf::Vector2f(0.0f, 50.0f));
//        states.transform.rotate(90.0f, m_ship->kinematics().position());
    sf::RectangleShape helm(sf::Vector2f(20.0f, 5.0f));
    target.draw(helm, states);
}