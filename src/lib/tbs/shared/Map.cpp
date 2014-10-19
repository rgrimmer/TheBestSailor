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

Map::Map() : m_width(0), m_height(0), m_container(NULL) {

}

Map::Map(int width, int height, double seed) : m_width(width), m_height(height) {
    assert(width >= 0 && height >= 0);

    ValueNoise::GenerateValues(seed);

    m_container = new float*[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_container[i] = new float[m_width];
    }

    float invWidth = 1.f / m_width, invHeight = 1.f / m_height;

    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_height; ++j) {
            sf::Vector2f pnoise(i * invWidth, j * invHeight);
            pnoise.x *= 20.0f;
            pnoise.y *= 20.0f;
            float n = ValueNoise::Eval(pnoise);
            m_container[i][j] = n;
        }
    }
}

Map::~Map() {

}

void Map::allocate(int width, int height) {
    m_width = width;
    m_height = height;
    
    m_container = new float*[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_container[i] = new float[m_width];
    }
}

int Map::getSize() const {
    return m_width * m_height;
}

int Map::getWidth() const {
    return m_width;
}

int Map::getHeight() const {
    return m_height;
}