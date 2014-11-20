/* 
 * File:   TileMap.cpp
 * Author: remy
 * 
 * Created on 9 octobre 2014, 15:49
 */

#include <iostream>

#include "shared/map/DrawWind.h"

void DrawWind::load(const WindMap &map) {

    int height = map.getHeight();
    int width = map.getWidth();
    
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
//            Wind wind = map(i,j).direction();
            float wind = 0;
            float cos1 = std::cos((wind + 10.0f) * 3.1415f / 180.0f);
            float sin1 = std::sin((wind + 10.0f) * 3.1415f / 180.0f);
            float cos2 = std::cos((wind - 10.0f) * 3.1415f / 180.0f);
            float sin2 = std::sin((wind - 10.0f) * 3.1415f / 180.0f);
            
            sf::Vector2f pos1 = triangle[0].position + sf::Vector2f(TILE_SIZE*cos1,TILE_SIZE*sin1);
            sf::Vector2f pos2 = triangle[0].position + sf::Vector2f(TILE_SIZE*cos2,TILE_SIZE*sin2);
            
            triangle[1].position = pos1;
            triangle[2].position = pos2;

            triangle[0].color = sf::Color(100, 255, 255, 255);
            triangle[1].color = sf::Color(255, 100, 255, 255);
            triangle[2].color = sf::Color(255, 255, 100, 255);
        }
    }
}

void DrawWind::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

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
