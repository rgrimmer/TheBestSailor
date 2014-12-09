/* 
 * File:   GlobalView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 11:54
 */


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

#include "shared/map/MapHeader.h"
#include "shared/Utils.h"

#include "client/GlobalView.h"

GlobalView::GlobalView() {
    // Set global view
    m_worldView = sf::View(sf::FloatRect(0.0f, 0.0f, m_mapHeader->getWidth() * TILE_SIZE, m_mapHeader->getHeight() * TILE_SIZE));
    
    // Set viewport for the view
    m_worldView.setViewport(sf::FloatRect(0.0f, 0.25f, 0.75f, 0.75f));
    
    // Set background image
    if(!m_background->loadFromFile("share/tbs/textures/wood1.jpg")) {
        std::cout << "Impossible de charger la texture de background";
    }
    
    loadInformation();
    // Set information view
//    m_informationView = sf::View();
    
        
    
}

GlobalView::~GlobalView() {
    
}

void GlobalView::loadInformation() {
    // on crée une texture de dessin de 500x500
//    m_informationTexture;
    if (!m_informationTexture.create(500, 500))
    {
        std::cout << "Impossible de créer la texture pour les informations" << std::endl;
    }

    
    m_informationTexture.clear();
    m_informationTexture.draw(sf::CircleShape(3)); // ou n'importe quel autre objet dessinable
    m_informationTexture.display();

}

void GlobalView::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    // pour dessiner, on utilise les mêmes fonctions

    // on récupère la texture (sur laquelle on vient de dessiner)
    const sf::Texture& texture = m_informationTexture.getTexture();
    
    // on la dessine dans la fenêtre
    sf::Sprite sprite(texture);
    target.draw(sprite);
    
}
