/* 
 * File:   HeigthMap.cpp
 * Author: maxence
 * 
 * Created on 10 octobre 2014, 13:39
 */
#include "shared/map/HeigthMap.h"

#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "shared/ValueNoise.h"

sf::Packet& operator<<(sf::Packet& packet, const HeigthMap& map) {
    return packet << map.getHeader();
}

HeigthMap::HeigthMap() : m_header(0, 0) {

}

HeigthMap::HeigthMap(const HeigthMap& other) :
HeigthMap(other.m_header) {
}

HeigthMap::HeigthMap(const MapHeader &header)
: m_header(header) {


    int width = header.getWidth();
    int height = header.getHeight();
    std::cout << width << " " << height << " " << getSeed() << std::endl;

    ValueNoise::GenerateValues(getSeed());

    m_container.resize(height);

    for (int i = 0; i < height; ++i) {
        m_container[i].resize(width);
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
}

HeigthMap::~HeigthMap() {
}

float HeigthMap::getValue(int x, int y) const {
    return m_container[x][y];
}

int HeigthMap::getSize() const {
    return m_header.getSize();
}

int HeigthMap::getWidth() const {
    return m_header.getWidth();
}

int HeigthMap::getHeight() const {
    return m_header.getHeight();
}

int HeigthMap::getSeed() const {
    return m_header.getSeed();
}

const MapHeader& HeigthMap::getHeader() const {
    return m_header;
}

MapHeader& HeigthMap::getHeader() {
    return m_header;
}