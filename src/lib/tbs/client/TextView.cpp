/* 
 * File:   TextView.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 11:37
 */

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "client/TextView.h"

sf::RenderStates TextView::g_states = sf::RenderStates::Default;
bool TextView::g_absView = true;
sf::IntRect TextView::g_prevViewport;

TextView::TextView(const std::string& text, int size, TypeAlign type, sf::Uint32 style)
: m_text(text)
, m_size(size)
, m_type(type)
, m_style(style) {

}

TextView::~TextView() {

}

void TextView::update() {
    g_states = sf::RenderStates::Default;
}

void TextView::draw(sf::RenderTarget& target, sf::RenderStates) const {
    if (target.getViewport(target.getView()) != g_prevViewport) {
        g_prevViewport = target.getViewport(target.getView());
        TextView::update();
    }

    if (g_absView) {
        sf::View curV = target.getView();
        target.setView(target.getDefaultView());
        drawText(target);
        target.setView(curV);
    } else {
        drawText(target);
    }
}

void TextView::drawText(sf::RenderTarget& target) const {
    sf::Text sfText(m_text, Font::getFont(), m_size);
    sfText.setStyle(m_style);
    sf::RectangleShape textShape(sf::Vector2f(sfText.getLocalBounds().width, sfText.getLocalBounds().height));
    textShape.setFillColor(sf::Color::Transparent);
    textShape.setOutlineThickness(6.0f);
    if (m_type == Regular) {
        target.draw(sfText, g_states);
        //        target.draw(textShape, g_states);
    } else {
        sf::RenderStates stateCpy(g_states);
        stateCpy.transform.translate(target.getView().getCenter().x - (sfText.getLocalBounds().width / 2.0f), 0);
        target.draw(sfText, stateCpy);
        //        target.draw(textShape, stateCpy);
    }
    g_states.transform.translate(0, sfText.getGlobalBounds().height + 12);
}

void TextView::setAbs(bool drawAbs) {
    g_absView = drawAbs;
}
