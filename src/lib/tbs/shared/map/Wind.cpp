/* 
 * File:   Wind.cpp
 * Author: maxence
 * 
 * Created on 28 octobre 2014, 23:06
 */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "shared/Utils.h"

#include "shared/map/Wind.h"
//
const int Wind::maxStrength = 150;
const int Wind::minStrength = 30;

Wind::Wind() {
}

Wind::Wind(int strength, float direction) :
m_strength(strength),
m_direction(direction)
{
//    std::cout << "dir" << direction << std::endl;
    setRotation(direction);
}

Wind::Wind(const Wind& orig) {
}

Wind::~Wind() {
}

void Wind::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(getVertices(), states);
}


sf::VertexArray Wind::getVertices() const {
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
}
