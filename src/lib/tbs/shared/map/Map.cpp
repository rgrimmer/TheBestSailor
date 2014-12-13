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

Map::Map() {
}

Map::Map(const MapHeader& header)
: m_header(header)
, m_heightMap(header)
, m_windMap(header) {

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
