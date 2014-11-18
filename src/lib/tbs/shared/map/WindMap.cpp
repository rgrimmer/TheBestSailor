/* 
 * File:   WindMap.cpp
 * Author: maxence
 * 
 * Created on 07 novembre 2014, 13:39
 */
#include "shared/map/WindMap.h"

#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "shared/ValueNoise.h"

WindMap::WindMap() : m_header(MapHeader(0,0)), m_container(NULL) {

}

WindMap::WindMap(const MapHeader &header) {

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
            m_container[i][j] = n*360.0f;
        }
    }
}

    

WindMap::~WindMap() {
    for (int i = 0; i < getHeight(); ++i) {
        delete m_container[i];
    }
    delete m_container;
}

int WindMap::getSize() const {
    return m_header.getSize();
}

int WindMap::getWidth() const {
    return m_header.getWidth();
}

int WindMap::getHeight() const {
    return m_header.getHeight();
}

int WindMap::getSeed() const {
    return m_header.getSeed();
}

const MapHeader& WindMap::getHeader() const {
    return m_header;
}

MapHeader& WindMap::getHeader() {
    return m_header;
}







/*
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
//    std::cout << "north : " << windDirection::north << std::endl;
//    std::cout << "southEast : " << windDirection::southEast << std::endl;
    int seed = header.getSeed();

    Rand random(seed);
    m_windDirection = random.getNextFloat(360);
    m_windStrength = random.getNextInt(20, 100);

    int size = m_header.getSize();
    m_winds = new DrawWind[size];

    int height = m_header.getHeight();
    int width = m_header.getWidth();
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            float n = ValueNoise::Eval(sf::Vector2f((float) i / width * 10.0f, (float) j / height * 10.0f));
            m_winds[j * m_header.getWidth() + i] = DrawWind(random.getNextInt(DrawWind::minStrength, DrawWind::maxStrength), n * 360);
        }
    }
}

DrawWind& WindMap::wind(int x, int y) {
    return m_winds[x + y * m_header.getWidth()];
}

const DrawWind& WindMap::wind(int x, int y) const {
    return m_winds[x + y * m_header.getWidth()];
}

DrawWind& WindMap::wind(const sf::Vector2i& point) {
    return wind(point.x, point.y);
}

const DrawWind& WindMap::wind(const sf::Vector2i& point) const {
    return wind(point.x, point.y);
}

WindMap::~WindMap() {
}

*/