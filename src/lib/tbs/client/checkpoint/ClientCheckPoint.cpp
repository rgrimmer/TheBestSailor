#include "shared/Utils.h"
#include "client/checkpoint/ClientCheckPoint.h"

ClientCheckPoint::ClientCheckPoint(sf::Vector2i position) 
: m_position(position)
, m_shape({200.0f, 200.0f})
, m_eState(e_state_off)
{
    m_shape.setPosition(position.x, position.y);
    m_shape.setFillColor(sf::Color::Red);
}



ClientCheckPoint::~ClientCheckPoint() {
}

void ClientCheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void ClientCheckPoint::activate() {
    m_shape.setFillColor(sf::Color::Green);
    m_eState = e_state_on;
}

