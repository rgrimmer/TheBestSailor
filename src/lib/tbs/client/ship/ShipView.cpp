/* 
 * File:   DrawShip.cpp
 * Author: maxence
 * 
 * Created on 29 novembre 2014, 10:43
 */

#include <iostream>

#include "shared/ship/Ship.h"

#include "client/VectorView.h"
#include "client/ship/ShipView.h"

ShipView::ShipView(const Ship &ship)
: m_ship(ship)
, m_sailShape({100.0f, 2.0f}) {
    m_speedView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().speed(), "Vship", sf::Color::Cyan);
    m_accView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().acceleration(), "", sf::Color::White);

    // Ship base
    m_shipVertex.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);
    m_shipVertex.append(sf::Vertex(sf::Vector2f(50.0f, 0.0f), sf::Color::Red));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(25.0f, 25.0f), sf::Color::Red));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(25.0f, -25.0f), sf::Color::Red));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(-50.0f, 25.0f), sf::Color::Red));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(-50.0f, -25.0f), sf::Color::Red));

    // Sail
    m_sailShape.setOrigin(0.0f, 1.0f);
    m_sailShape.setFillColor(sf::Color::White);
}

ShipView::ShipView(const ShipView& other)
: m_ship(other.m_ship)
, m_speedView(other.m_speedView)
, m_accView(other.m_accView)
, m_shipVertex(other.m_shipVertex)
, m_sailShape(other.m_sailShape) {
    m_speedView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().speed(), "Vship", sf::Color::Cyan);
    m_accView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().acceleration(), "", sf::Color::White);
}

ShipView::~ShipView() {
    delete m_speedView;
    delete m_accView;
}

void ShipView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = states.transform.Identity;
    states.transform.translate(m_ship.kinematics().position());
    states.transform.rotate(m_ship.getAngle());

    // Draw ship
    target.draw(m_shipVertex, states);

    // Draw sail
    states.transform = states.transform.Identity;
    states.transform.translate(m_ship.kinematics().position());
    states.transform.rotate(m_ship.getSail().getAngle());
    target.draw(m_sailShape, states);

    // Draw speed vector
    target.draw(*m_speedView);

    // Draw acceleration vector
    target.draw(*m_accView);

    /*
    // Draw helm
        states.transform.translate(sf::Vector2f(0.0f, 50.0f));
//        states.transform.rotate(90.0f, m_ship->kinematics().position());
    sf::RectangleShape helm(sf::Vector2f(20.0f, 5.0f));
    target.draw(helm, states);*/

}

const Ship& ShipView::getShip() const {
    return m_ship;
}
