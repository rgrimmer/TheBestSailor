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
#include "shared/MapHeader.h"

Map::Map() : m_header(MapHeader(0,0)), m_container(NULL) {

}

Map::Map(const MapHeader &header) : m_header(header) {

    ValueNoise::GenerateValues(getSeed());

    m_container = new float*[getHeight()];

    for (int i = 0; i < getHeight(); ++i) {
        m_container[i] = new float[getWidth()];
    }

    float invWidth = 1.f / getWidth(), invHeight = 1.f / getHeight();

    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            sf::Vector2f pnoise(i * invWidth, j * invHeight);
            pnoise.x *= 20.0f;
            pnoise.y *= 20.0f;
            float n = ValueNoise::Eval(pnoise);
            m_container[i][j] = n;
        }
    }
}

    

Map::~Map() {
    for (int i = 0; i < getHeight(); ++i) {
        delete m_container[i];
    }
    delete m_container;
}

int Map::getSize() const {
    return m_header.getSize();
}

int Map::getWidth() const {
    return m_header.getWidth();
}

int Map::getHeight() const {
    return m_header.getHeight();
}

double Map::getSeed() const {
    return m_header.getSeed();
}

MapHeader Map::getHeader() const {
    return m_header;
}