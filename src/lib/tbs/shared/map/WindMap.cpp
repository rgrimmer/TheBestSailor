/* 
 * File:   WindMap.cpp
 * Author: maxence
 * 
 * Created on 27 octobre 2014, 19:44
 */

#include "shared/map/WindMap.h"
#include "shared/Rand.h"
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include "shared/Utils.h"
#include "shared/ValueNoise.h"

WindMap::WindMap() {
}

WindMap::WindMap(const MapHeader &header)
: m_header(header) {
    std::cout << "north : " << windDirection::north << std::endl;
    std::cout << "southEast : " << windDirection::southEast << std::endl;
    int seed = header.getSeed();

    Rand random(seed);
    m_windDirection = random.getNextFloat(360);
    m_windStrength = random.getNextInt(20, 100);

    int size = m_header.getSize();
    m_winds = new Wind[size];
    
    int height = m_header.getHeight();
    int width = m_header.getWidth();
    for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
        float n = ValueNoise::Eval(sf::Vector2f((float)i/width*10.0f, (float)j/height*10.0f));
        m_winds[j*m_header.getWidth() + i] = Wind(random.getNextInt(20, 100), m_windDirection+( (n-0.5f) * 45.0f));
    }
    }
}

void WindMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    int heigth = m_header.getHeight();
    int width = m_header.getWidth();
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            target.draw(m_winds[i * width + j], states);
            states.transform.translate(TILE_SIZE, 0);
        }
        states.transform.translate(-TILE_SIZE * width, TILE_SIZE);
    }
}

WindMap::~WindMap() {
}

