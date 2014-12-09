/* 
 * File:   DisplayInfo.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 11:37
 */

#include <SFML/Graphics/Text.hpp>

#include "client/DisplayInfo.h"

sf::RenderWindow *DisplayInfo::m_window;
sf::RenderStates DisplayInfo::m_states;
float DisplayInfo::m_zoom(1.0f);

void DisplayInfo::setWindow(sf::RenderWindow* window) {
    m_window = window;
}

void DisplayInfo::setTopLeftPosition(const sf::Vector2f &position) {
    m_states = sf::RenderStates(sf::Transform().translate(position));
}

void DisplayInfo::setZoom(float zoom) {
    DisplayInfo::m_zoom = zoom;
}

void DisplayInfo::draw(const std::string &text) {
    
    sf::Text sfText(text, Font::getFont(), 20 * DisplayInfo::m_zoom);
    m_window->draw(sfText, m_states);
    m_states.transform.translate(0,sfText.getCharacterSize() + 2);
}