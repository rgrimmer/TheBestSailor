/* 
 * File:   Map.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:48
 */

#include "shared/map/Map.h"

sf::Packet& operator<<(sf::Packet& packet, const Map& map) {
    return packet << map.getHeightMap() << map.getWindMap();
}

sf::Packet& operator>>(sf::Packet& packet, Map& map) {
    // @TODO : Redo
    MapHeader headerHeightMap, headerWindMap;
    packet >> headerHeightMap >> headerWindMap;
    map = Map(headerHeightMap);
    return packet;
}

Map::Map() {
}

Map::Map(int width, int height, int heightMapSeed, int windMapSeed)
: m_header(width, height, heightMapSeed)
, m_heightMap(m_header)
, m_windMap(MapHeader(width, height, windMapSeed)) {
}

Map::Map(const MapHeader& header)
: m_header(header)
, m_heightMap(header)
, m_windMap(header) {
    // @TODO remade : generate 2 seed (1 for heightMap and 1 for windMAp) from header parameter seed
}

Map::~Map() {
}

const MapHeader& Map::getHeader() const {
    return m_header;
}

const HeigthMap& Map::getHeightMap() const {
    return m_heightMap;
}

const WindMap& Map::getWindMap() const {
    return m_windMap;
}

MapHeader& Map::getHeader() {
    return m_header;
}

HeigthMap& Map::getHeightMap() {
    return m_heightMap;
}

WindMap& Map::getWindMap() {
    return m_windMap;
}

Wind& Map::getWind(const sf::Vector2i& windPos) {
    return m_windMap.wind(windPos);
}

const Wind Map::getWind(const sf::Vector2i& windPos) const {
    return m_windMap.wind(windPos);
}
