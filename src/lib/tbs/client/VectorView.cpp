/* 
 * File:   VectorView.cpp
 * Author: maxence
 * 
 * Created on 28 novembre 2014, 13:08
 */

#include <SFML/Graphics/RenderTarget.hpp>

#include "client/VectorView.h"
#include "shared/Utils.h"

const sf::Vector2f VectorView::defaultOrigin(0, 0);

VectorView::VectorView(const sf::Vector2f& origin, const sf::Vector2f& vector, const std::string& vectorName, const sf::Color& color)
: m_origin(origin)
, m_vector(vector)
, m_vectorName(vectorName)
, m_color(color) {
    if (!m_vectorName.empty()) {
        m_textVector = sf::Text(m_vectorName, Font::getFont());
        m_textVector.setOrigin(-0.02f, m_textVector.getCharacterSize());
        m_textVector.setColor(m_color);
        m_textVector.scale(1.0f/200.0f, 1.0f/200.0f);
    }
}

VectorView::VectorView(const sf::Vector2f& vector, const std::string& vectorName, const sf::Color& color)
: VectorView(defaultOrigin, vector, vectorName, color) {
}

VectorView::~VectorView() {

}

sf::Vector2f VectorView::getVector() const {
    return m_vector;
}

void VectorView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(m_origin.x, m_origin.y);
    states.transform.rotate(Kinematics::direction(m_vector));
    
    // Line
    sf::RectangleShape lineVector(sf::Vector2f(Kinematics::norme(m_vector), 0.02f));
    lineVector.setFillColor(m_color);
    target.draw(lineVector, states);

    // Text
    if (!m_vectorName.empty()) {
        states.transform.translate(lineVector.getPoint(2));
        target.draw(m_textVector, states);
    }
}

