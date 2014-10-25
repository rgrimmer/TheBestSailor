/* 
 * File:   Map.cpp
 * Author: maxence
 * 
 * Created on 10 octobre 2014, 13:39
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include "shared/entity/map/Map.h"
#include "shared/ValueNoise.h"

Map::Map() : m_header(MapHeader(0,0)), m_container(NULL) {

}

Map::Map(const MapHeader &header) {

    m_header.setWidth(header.getWidth());
    m_header.setHeight(header.getHeight());
    m_header.setSeed(header.getSeed());
    
    int width = header.getWidth();
    int height = header.getHeight();

    ValueNoise::GenerateValues(getSeed());

    m_container = new float*[height];

    for (int i = 0; i < height; ++i) {
        m_container[i] = new float[width];
    }

    float invWidth = 1.f / width, invHeight = 1.f / height;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::Vector2f pnoise(i * invWidth, j * invHeight);
            pnoise.x *= 20.0f;
            pnoise.y *= 20.0f;
            float n = ValueNoise::Eval(pnoise);
            m_container[i][j] = n;
        }
    }
    std::cout << "map create : " << getWidth() << " " << getHeight() << " " << getSeed() << std::endl;
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

int Map::getSeed() const {
    return m_header.getSeed();
}

const MapHeader& Map::getHeader() const {
    return m_header;
}

MapHeader& Map::getHeader() {
    return m_header;
}