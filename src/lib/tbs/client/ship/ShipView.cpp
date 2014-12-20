/* 
 * File:   DrawShip.cpp
 * Author: maxence
 * 
 * Created on 29 novembre 2014, 10:43
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "client/ship/ShipView.h"

ShipView::ShipView(const Ship &ship)
: m_ship(ship)
, m_shipShape(sf::Vector2f(100.0f, 50.0f)) {
    m_speedView = new VectorView<float>(m_ship.kinematics().speed(), "Vship", sf::Color::Cyan);
    m_accView = new VectorView<float>(m_ship.kinematics().acceleration(), "", sf::Color::White);
    
    m_shipShape.setOrigin(50.0f, 25.0f);
    m_shipShape.setFillColor(sf::Color::Red);
    //m_shipShape.setPosition(m_ship.kinematics().position());
}

ShipView::~ShipView() {
    delete m_speedView;
    delete m_accView;
}

void ShipView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.transform.rotate(m_ship.getAngle(), m_ship.kinematics().position());
    states.transform.translate(m_ship.kinematics().position());
    
    // Draw ship
    target.draw(m_shipShape, states);

    states.transform = states.transform.Identity;
    states.transform.translate(m_ship.kinematics().position());
    states.transform.rotate(m_ship.getSail().getAngle());
    
    // Draw sail
    target.draw(m_ship.getSail(), states);
    
    // Draw speed vector
    states.transform = states.transform.Identity;
    states.transform.translate(m_ship.kinematics().position());
    states.transform.rotate(Kinematics::direction(m_speedView->getVector()));
    target.draw(*m_speedView, states);
    
    // Draw acceleration vector
    states.transform = states.transform.Identity;
    states.transform.translate(m_ship.kinematics().position());
    states.transform.rotate(Kinematics::direction(m_accView->getVector()));
    target.draw(*m_accView, states);
    
    /*
    // Draw helm
        states.transform.translate(sf::Vector2f(0.0f, 50.0f));
//        states.transform.rotate(90.0f, m_ship->kinematics().position());
    sf::RectangleShape helm(sf::Vector2f(20.0f, 5.0f));
    target.draw(helm, states);*/
    
}
