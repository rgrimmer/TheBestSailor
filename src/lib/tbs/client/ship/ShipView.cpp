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
#include "shared/Utils.h"

ShipView::ShipView(const Ship &ship, const sf::Color & color)
: m_ship(ship)
, m_sailShape({0.5f, 0.05f}) {
    m_speedView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().speed(), "Vship", sf::Color::Cyan);
    m_accView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().acceleration(), "", sf::Color::White);

    // Ship base
    m_shipVertex.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);
    m_shipVertex.append(sf::Vertex(sf::Vector2f(0.4f, 0.0f), color));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(0.2f, 0.2f), color));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(0.2f, -0.2f), color));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(-0.4f, 0.2f), color));
    m_shipVertex.append(sf::Vertex(sf::Vector2f(-0.4f, -0.2f), color));

    // Sail
    m_sailShape.setOrigin(0.0f, 0.05f);
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
    
    sf::RenderStates renderShipShape(states);
    renderShipShape.transform.translate(m_ship.kinematics().position());
    renderShipShape.transform.rotate(m_ship.getAngle());

    // Draw ship
    target.draw(m_shipVertex, renderShipShape);

    // Draw sail
    sf::RenderStates renderSailShape(states);
    renderSailShape.transform.translate(m_ship.kinematics().position());
    renderSailShape.transform.rotate(m_ship.getSail().getAngle());
    target.draw(m_sailShape, renderSailShape);

    // Draw speed vector
    target.draw(*m_speedView, states);

    // Draw acceleration vector
    target.draw(*m_accView, states);
}

const Ship& ShipView::getShip() const {
    return m_ship;
}
