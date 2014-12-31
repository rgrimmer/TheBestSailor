/* 
 * File:   BackgroundView.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 11:29
 */

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "client/BackgroundView.h"


bool BackgroundView::g_textureIsLoad(false);
sf::Texture BackgroundView::g_texture;

sf::Texture& BackgroundView::getTexture() {
    if (!g_textureIsLoad) {
        if (!g_texture.loadFromFile("share/tbs/textures/wood1.png")) {
            std::cout << "[Err] \t Warrning : texture of 'wood1.png' not found" << std::endl;
        }
        g_textureIsLoad = true;
    }
    return g_texture;
}

BackgroundView::BackgroundView() 
: m_background(getTexture()){
    sf::Texture& texture = getTexture();
//    m_background.setTexture(texture);
    m_backgroundView = sf::View(sf::FloatRect(0.0f, 0.0f, texture.getSize().x, texture.getSize().y));
}

BackgroundView::~BackgroundView() {
}

void BackgroundView::draw(sf::RenderTarget& target, sf::RenderStates) const {
    sf::View currentView = target.getView();

    target.setView(m_backgroundView);
    target.draw(m_background);

    target.setView(currentView);
}
