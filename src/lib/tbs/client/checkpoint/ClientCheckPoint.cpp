#include "client/checkpoint/ClientCheckPoint.h"

ClientCheckPoint::ClientCheckPoint(sf::Vector2i position) 
: m_position(position)
, m_shape({30.0f, 30.0f})
{
    m_shape.setPosition(static_cast<sf::Vector2f>(position));
    m_shape.setFillColor(sf::Color::Red);
}

ClientCheckPoint::~ClientCheckPoint() {
}

void ClientCheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(m_shape, states);
}