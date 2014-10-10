/* 
 * File:   Map.cpp
 * Author: maxence
 * 
 * Created on 10 octobre 2014, 13:39
 */

#include "Map.h"

Map::Map() : m_container(NULL), m_width(0), m_height(0) {
}

Map::Map(const Map& orig) {
    m_width = orig.width();
    m_height = orig.height();

    int mapSize = orig.size();
    m_container = new auto[mapSize];

    for (unsigned i = 0; i < mapSize; ++i)
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
    m_container = new auto[width * height];

    // Generation

    float invImageWidth = 1.f / width, invImageHeight = 1.f / height;
    ValueNoise simpleNoise2D;
    float level[width * height];

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            sf::Vector2f pnoise(i * invImageWidth, j * invImageHeight);
            pnoise.x *= 10.0f;
            pnoise.y *= 10.0f;
            float n = simpleNoise2D.Eval(pnoise);
            level[i + j * width] = n;
        }
    }
}

sf::Packet& Map::operator<<(sf::Packet &packet, const Map &map) {
    int mapSize = map.size();

    // @TODO check syntaxe of cast
    packet << (sf::Int32) map.width() << (sf::Int32) map.height();
    
    for (int i = 0; i < mapSize; ++i)
        packet << map[i];

    return packet;
}

sf::Packet& operator>>(sf::Packet &packet, Map &map) {
    int mapSize = map.size();

    assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);

    packet >> map.rwidth() >> map.rheight(); 
    
    for (int i = 0; i < mapSize; ++i)
        packet >> map[i];

    return packet;
}

