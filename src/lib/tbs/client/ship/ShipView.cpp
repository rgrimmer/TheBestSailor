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
#include "shared/Utils.h"

sf::Texture ShipView::g_texture;

ShipView::ShipView(const Ship &ship, const sf::Color & color)
: m_ship(ship)
, m_sailShape({0.5f, 0.05f}) {
    m_speedView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().speed(), "Vship", sf::Color::Cyan);
    m_accView = new VectorView(m_ship.kinematics().position(), m_ship.kinematics().acceleration(), "", sf::Color::White);
    
    g_texture.loadFromFile("share/tbs/textures/boat.png");
    m_boatSprite.setTexture(g_texture);
    m_boatSprite.setScale(1.5f / m_boatSprite.getTexture()->getSize().x, 0.5f / m_boatSprite.getTexture()->getSize().y);
    m_boatSprite.setOrigin(m_boatSprite.getTexture()->getSize().x/2.0f, m_boatSprite.getTexture()->getSize().y/2.0f);
    
    // Sail
    m_sailShape.setOrigin(0.0f, 0.05f);
    m_sailShape.setFillColor(sf::Color::White);
}

ShipView::ShipView(const ShipView& other)
: ShipView(other.m_ship, sf::Color::Red){
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
    target.draw(m_boatSprite, renderShipShape);

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
