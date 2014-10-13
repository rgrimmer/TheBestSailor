/* 
 * File:   Map.cpp
 * Author: maxence
 * 
 * Created on 10 octobre 2014, 13:39
 */

#include "shared/Map.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "shared/ValueNoise.h"

Map::Map() : m_container(NULL), m_width(0), m_height(0) {
}

Map::Map(const Map& orig) {
    m_width = orig.width();
    m_height = orig.height();

    int mapSize = orig.size();
    m_container = new float[mapSize];

    for (int i = 0; i < mapSize; ++i)
        m_container[i] = orig[i];
}

Map::~Map() {
    delete m_container;
}

void Map::generate(int width, int height) {
    assert(width >= 0 && height >= 0);

    delete m_container;

    m_width = width;
    m_height = height;
    m_container = new float[width * height];

    // Generation

    float invImageWidth = 1.0f / width, invImageHeight = 1.0f / height;
    ValueNoise simpleNoise2D;
    
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            sf::Vector2f pnoise(i * invImageWidth, j * invImageHeight);
            pnoise.x *= 10.0f;
            pnoise.y *= 10.0f;
            float n = simpleNoise2D.Eval(pnoise);
            m_container[i + j * width] = n;
        }
    }
}
