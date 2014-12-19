/* 
 * File:   WindMapView.cpp
 * Author: remy
 * 
 * Created on 9 octobre 2014, 15:49
 */

#include <iostream>
#include <math.h>

#include "client/map/WindMapView.h"

WindMapView::WindMapView(const WindMap& windMap) 
: m_windMap(windMap) {
    load();
}

void WindMapView::load() {

    int height = m_windMap.getHeight();
    int width = m_windMap.getWidth();
    
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 3);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {

            // get a pointer to the current tile's triangle
            sf::Vertex* triangle = &m_vertices[(i + j * width) * 3];

            // define its 3 corners
            triangle[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            
            //Wind wind = map(i,j).direction();
            Wind wind = m_windMap.wind(i,j);
            float windDir = wind.direction();
            float cos1 = std::cos((windDir + 15.0f) * M_PI / 180.0f);
            float sin1 = std::sin((windDir + 15.0f) * M_PI / 180.0f);
            float cos2 = std::cos((windDir - 15.0f) * M_PI / 180.0f);
            float sin2 = std::sin((windDir - 15.0f) * M_PI / 180.0f);
            
            sf::Vector2f pos1 = triangle[0].position + sf::Vector2f(TILE_SIZE/1.5f*cos1,TILE_SIZE/1.5f*sin1);
            sf::Vector2f pos2 = triangle[0].position + sf::Vector2f(TILE_SIZE/1.5f*cos2,TILE_SIZE/1.5f*sin2);
            
            triangle[1].position = pos1;
            triangle[2].position = pos2;

            int valTrans = 255 * (wind.force() - WindMap::minStrength) / (WindMap::maxStrength - WindMap::minStrength);
//            int valTrans = 255;
            triangle[0].color = sf::Color(255, 255, 255, valTrans);
            triangle[1].color = sf::Color(255, 255, 255, valTrans);
            triangle[2].color = sf::Color(255, 255, 255, valTrans);
        }
    }
}

void WindMapView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform.translate(TILE_SIZE/2, TILE_SIZE/2);

    // draw the vertex array
    target.draw(m_vertices, states);
}
















/*
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "shared/Utils.h"

#include "shared/map/DrawWind.h"
//
const int DrawWind::maxStrength = 150;
const int DrawWind::minStrength = 30;

DrawWind::DrawWind() {
}

DrawWind::DrawWind(int strength, float direction) :
m_strength(strength),
m_direction(direction)
{
//    std::cout << "dir" << direction << std::endl;
    setRotation(direction);
}

DrawWind::DrawWind(const DrawWind& orig) {
}

DrawWind::~DrawWind() {
}

void DrawWind::load(const WindMap &map) {
    
}

void DrawWind::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(getVertices(), states);
}


sf::VertexArray DrawWind::getVertices() const {
    sf::VertexArray vertices;
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(3);
     // get a pointer to the current tile's quad
    sf::Vertex* triangle = &vertices[0];

    // define its 3 corners
    triangle[0].position = sf::Vector2f(0, 0); 
    triangle[1].position = sf::Vector2f(-TILE_SIZE/8.0f, TILE_SIZE/2.0f);
    triangle[2].position = sf::Vector2f(TILE_SIZE/8.0f, TILE_SIZE/2.0f);
    int colorVal = (float) m_strength / (maxStrength - minStrength) * 255;
    triangle[0].color = sf::Color(colorVal, colorVal, colorVal, 125);
    triangle[1].color = triangle[0].color;
    triangle[2].color = triangle[0].color;
//    sf::Color()
    
    return vertices;
}*/
