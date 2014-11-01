/* 
 * File:   DisplayInfo.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 11:37
 */

#include <SFML/Graphics/Text.hpp>

#include "client/DisplayInfo.h"

DisplayInfo::DisplayInfo(sf::RenderWindow* window, const sf::Font* font) :
m_window(window), m_font(font), m_zoom(1.0f) {
}

DisplayInfo::~DisplayInfo() {
}

void DisplayInfo::setTopLeftPosition(const sf::Vector2f &position) {
    m_states = sf::RenderStates(sf::Transform().translate(position));
}

void DisplayInfo::zoom(float zoom) {
    m_zoom = zoom;
}

void DisplayInfo::draw(const std::string &text) {
    
    sf::Text sfText(text, *m_font, 30 * m_zoom);
    m_window->draw(sfText, m_states);
    m_states.transform.translate(0,sfText.getCharacterSize() + 2);
}