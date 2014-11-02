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
//    std::cout << "north : " << windDirection::north << std::endl;
//    std::cout << "southEast : " << windDirection::southEast << std::endl;
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
            float n = ValueNoise::Eval(sf::Vector2f((float) i / width * 10.0f, (float) j / height * 10.0f));
            m_winds[j * m_header.getWidth() + i] = Wind(random.getNextInt(Wind::minStrength, Wind::maxStrength), n * 360);
        }
    }
}

#include <iostream>

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

Force WindMap::force(const sf::Vector2f& point) {
    Force force;

    sf::Vector2i tileSize(TILE_SIZE, TILE_SIZE);    
    sf::Vector2i corner((int) point.x - ((int) point.x % tileSize.x), (int) point.y - ((int) point.y % tileSize.y));
    force.angle() = wind(corner.x / tileSize.x, corner.y / tileSize.y).getRotation();
/*
    sf::Vector2f corner[4];

//    std::cout << point.x << " " << point.y << std::endl;
    sf::Vector2f tileSize(TILE_SIZE, TILE_SIZE);

    corner[0] = sf::Vector2f(   (int) point.x - ((int) point.x % (int)tileSize.x), (int) point.y - ((int) point.y % (int) tileSize.y));
    corner[1] = corner[0] + tileSize;
    corner[2] = sf::Vector2f(corner[0].x, corner[1].y);
    corner[3] = sf::Vector2f(corner[1].x, corner[0].y);
//    std::cout << "[c0] " << corner[0].x << " " << corner[0].y;
//    std::cout << " [c1] " << corner[1].x << " " << corner[1].y;
//    std::cout << " [c2] " << corner[2].x << " " << corner[2].y;
//    std::cout << " [c3] " << corner[3].x << " " << corner[3].y;
//    std::cout << std::endl;


    for (int i = 0; i < 4; ++i) {

        sf::Vector2f dist = corner[i] - point;
        sf::Vector2f distAbs(std::abs(dist.x), std::abs(dist.y));
        sf::Vector2f pourcent = sf::Vector2f(1.0f, 1.0f) - sf::Vector2f(distAbs.x / tileSize.x, distAbs.y / tileSize.y);
        float angle = wind(corner[i].x / tileSize.x, corner[i].y / tileSize.y).getRotation();
        force.angle() += (pourcent.x + pourcent.y) * angle /4;
//        std::cout << "[" << i << "]" << angle << " " << pourcent.x + pourcent.y << " ";
    }
//    std::cout << std::endl;
*/
    return force;
}

Wind& WindMap::wind(int x, int y) {
    return m_winds[x + y * m_header.getWidth()];
}

const Wind& WindMap::wind(int x, int y) const {
    return m_winds[x + y * m_header.getWidth()];
}

Wind& WindMap::wind(const sf::Vector2i& point) {
    return wind(point.x, point.y);
}

const Wind& WindMap::wind(const sf::Vector2i& point) const {
    return wind(point.x, point.y);
}

WindMap::~WindMap() {
}

