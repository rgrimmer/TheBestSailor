/* 
 * File:   TileMap.cpp
 * Author: remy
 * 
 * Created on 9 octobre 2014, 15:49
 */

#include <SFML/Graphics.hpp>

#include "../shared/Sharable.h"

class TileMap : public sf::Drawable, public sf::Transformable, public Sharable {
    
public:

    void load(sf::Vector2u tileSize, const float* tiles, unsigned int width, unsigned int height);
    virtual sf::Packet serialize();


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};