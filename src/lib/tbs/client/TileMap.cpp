/* 
 * File:   TileMap.cpp
 * Author: remy
 * 
 * Created on 9 octobre 2014, 15:49
 */

#include <SFML/Network/Packet.hpp>

#include "client/TileMap.h"
#include "client/Gradient.h"

void TileMap::load(sf::Vector2u tileSize, const Map &map) {

    // @TODO
    Gradient g;
    g.CreateGradient();

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(map.width() * map.height() * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            // get the current tile number
            float tileValue = map[i + j * map.width()];

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * map.width()) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            sf::Color c(g.GradientR[(int) (tileValue * 255)], g.GradientG[(int) (tileValue * 255)], g.GradientB[(int) (tileValue * 255)], 255);

            // define its 4 colors coordinates
            quad[0].color = c;
            quad[1].color = c;
            quad[2].color = c;
            quad[3].color = c;
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
