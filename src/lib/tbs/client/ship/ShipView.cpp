/* 
 * File:   DrawShip.cpp
 * Author: maxence
 * 
 * Created on 29 novembre 2014, 10:43
 */

#include <iostream>

#include "shared/ship/Ship.h"

#include "client/view/VectorView.h"
#include "client/view/ShipView.h"

ShipView::ShipView(const Ship &ship, const sf::Color & color)
: m_ship(ship) {
    m_speedView = new VectorView(m_ship.getPosition(), m_ship.getVelocity(), "Vship", sf::Color::Cyan);

    std::string pathShip = "share/tbs/textures/baseShip" + std::to_string(m_ship.getType()) + ".png";
    std::string pathSail = "share/tbs/textures/sail" + std::to_string(m_ship.getType()) + ".png";

    if (!m_textureShip.loadFromFile(pathShip))
        m_textureShip.loadFromFile("share/tbs/textures/baseShip.png");
    
    if (!m_textureSail.loadFromFile(pathSail))
        m_textureSail.loadFromFile("share/tbs/textures/sail1.png");

    sf::Vector2f sizeShip = static_cast<sf::Vector2f>(m_textureShip.getSize());
    sf::Vector2f sizeSail = static_cast<sf::Vector2f>(m_textureSail.getSize());
    m_shapeShip.setPrimitiveType(sf::PrimitiveType::Quads);
    m_shapeShip.append(sf::Vertex({-0.5f, -0.5f}, {0.0f, 0.0f}));
    m_shapeShip.append(sf::Vertex({0.5f, -0.5f}, {sizeShip.x, 0.0f}));
    m_shapeShip.append(sf::Vertex({0.5f, 0.5f}, {sizeShip.x, sizeShip.y}));
    m_shapeShip.append(sf::Vertex({-0.5f, 0.5f}, {0.0f, sizeShip.y}));
    
    m_shapeSail.setPrimitiveType(sf::PrimitiveType::Quads);
    m_shapeSail.append(sf::Vertex({-0.5f, -0.5f}, {0.0f, 0.0f}));
    m_shapeSail.append(sf::Vertex({0.5f, -0.5f}, {sizeSail.x, 0.0f}));
    m_shapeSail.append(sf::Vertex({0.5f, 0.5f}, {sizeSail.x, sizeSail.y}));
    m_shapeSail.append(sf::Vertex({-0.5f, 0.5f}, {0.0f, sizeSail.y}));
}

ShipView::ShipView(const ShipView& other)
: ShipView(other.m_ship, sf::Color::Red) {
}

ShipView::~ShipView() {
    delete m_speedView;
    //    delete m_accView;
}

void ShipView::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    sf::RenderStates renderShipShape(states);
    renderShipShape.transform.translate(m_ship.getPosition());
    renderShipShape.transform.rotate(m_ship.getAngle());

    // Draw ship
    renderShipShape.texture = &m_textureShip;
    target.draw(m_shapeShip, renderShipShape);

    // Draw sail
    sf::RenderStates renderSailShape(renderShipShape);
    renderSailShape.transform.translate({0.15,0.0});
    renderSailShape.transform.rotate(m_ship.getSail().getAngle() - m_ship.getAngle());
    renderSailShape.texture = &m_textureSail;
    target.draw(m_shapeSail, renderSailShape);

    // Draw speed vector
    target.draw(*m_speedView, states);
}

const Ship& ShipView::getShip() const {
    return m_ship;
}
