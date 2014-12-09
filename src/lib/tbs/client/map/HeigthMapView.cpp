/* 
 * File:   TileMap.cpp
 * Author: remy
 * 
 * Created on 9 octobre 2014, 15:49
 */

#include <iostream>

#include "client/map/HeigthMapView.h"
#include "client/map/Gradient.h"

HeigthMapView::HeigthMapView(const HeigthMap &heigthMap)
: m_heigthMap(heigthMap)
, m_squared(false) {
    load();
}

bool HeigthMapView::switchSquared() {
    m_squared = !m_squared;
    load();
    return m_squared;
}


void HeigthMapView::load() {

    int height = m_heigthMap.getHeight();
    int width = m_heigthMap.getWidth();
    
    sf::Color mapColor[width][height];

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            float tileValue = m_heigthMap(i,j);
            mapColor[i][j] = Gradient::gradient[(int) (tileValue * 255)]; //g.getColor((int) (tileValue * 255));
        }
    }

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

            // define its 4 colors coordinates
            if (m_squared) {
                sf::Color c = mapColor[i][j];
                quad[0].color = c;
                quad[1].color = c;
                quad[2].color = c;
                quad[3].color = c;
            } else {
                if (i < width && j < height) {
                    quad[0].color = mapColor[i][j];// + j * width];
                    quad[1].color = mapColor[i+1][j];// + j * width + 1];
                    quad[2].color = mapColor[i+1][j+1];// + (j + 1) * width + 1];
                    quad[3].color = mapColor[i][j+1];// + (j + 1) * width];
                }
            }

        }
    }
}

void HeigthMapView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    //states.transform *= getTransform();

    // draw the vertex array
    target.draw(m_vertices, states);
}