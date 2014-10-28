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

    for (int i = 0; i < size; i++) {
        m_winds[i] = Wind(m_windStrength, m_windDirection);
    }
}

void WindMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    int heigth = m_header.getHeight();
    int width = m_header.getWidth();
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            states.transform.translate(TILE_SIZE, 0);
            target.draw(m_winds[i * width + j], states);
        }
        states.transform.translate(-TILE_SIZE * width, TILE_SIZE);
    }
}

WindMap::~WindMap() {
}

