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

const int WindMap::maxStrength = 8;
const int WindMap::minStrength = WindMap::maxStrength / 2;

sf::Packet& operator<<(sf::Packet& packet, const WindMap& map) {
    return packet << map.getHeader();
}

WindMap::WindMap() : m_header(0, 0), m_container(nullptr) {

}

WindMap::WindMap(const MapHeader &header)
: m_header(header)
, m_container(nullptr) {
    if(m_header.getWidth() == 0 || m_header.getHeight() == 0)
        return;
    int width = header.getWidth();
    int height = header.getHeight();

    ValueNoise::GenerateValues(getSeed());

    m_container = new Wind*[height];

    for (int i = 0; i < height; ++i) {
        m_container[i] = new Wind[width];
    }

    float invWidth = 1.f / width, invHeight = 1.f / height;
    float mainDir = ValueNoise::Eval(sf::Vector2f(0.0f,0.0f));

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::Vector2f pnoise(i * invWidth, j * invHeight);
            float nDirection = ValueNoise::Eval(sf::Vector2f(pnoise.x * 5.0f, pnoise.y * 5.0f));
            //            float nDirection =45.0f/360.0f;
            float nForce = ValueNoise::Eval(sf::Vector2f(pnoise.x * 40.0f, pnoise.y * 40.0f));
            m_container[i][j] = Wind(mainDir + ( 120.0f * (nDirection - 0.5f)), nForce * (maxStrength - minStrength) + minStrength);
        }
    }
}

WindMap::~WindMap() {
    // @TODO replace wind* by vector
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
