/* 
 * File:   TileMap.cpp
 * Author: remy
 * 
 * Created on 9 octobre 2014, 15:49
 */

#include "client/TileMap.h"
#include "client/Gradient.h"



void TileMap::load(const float tiles[NB_TILES_WIDTH][NB_TILES_HEIGHT], bool squared) {

    sf::Color map[NB_TILES_WIDTH][NB_TILES_HEIGHT];

    for (unsigned int i = 0; i < NB_TILES_WIDTH; ++i) {
        for (unsigned int j = 0; j < NB_TILES_HEIGHT; ++j) {
            float tileValue = tiles[i][j];
            map[i][j] = Gradient::gradient[(int) (tileValue * 255)]; //g.getColor((int) (tileValue * 255));
        }
    }

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(NB_TILES_WIDTH * NB_TILES_HEIGHT * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < NB_TILES_WIDTH; ++i) {
        for (unsigned int j = 0; j < NB_TILES_HEIGHT; ++j) {

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * NB_TILES_WIDTH) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

            // define its 4 colors coordinates
            if (squared) {
                sf::Color c = map[i][j];
                quad[0].color = c;
                quad[1].color = c;
                quad[2].color = c;
                quad[3].color = c;
            } else {
                if (i < NB_TILES_WIDTH && j < NB_TILES_HEIGHT) {
                    quad[0].color = map[i][j];// + j * NB_TILES_WIDTH];
                    quad[1].color = map[i+1][j];// + j * NB_TILES_WIDTH + 1];
                    quad[2].color = map[i+1][j+1];// + (j + 1) * NB_TILES_WIDTH + 1];
                    quad[3].color = map[i][j+1];// + (j + 1) * NB_TILES_WIDTH];
                }
            }

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