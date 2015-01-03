/* 
 * File:   MapHeader.cpp
 * Author: maxence
 * 
 * Created on 19 octobre 2014, 16:23
 */

#include "shared/map/MapHeader.h"

sf::Packet& operator<<(sf::Packet& packet, const MapHeader& header) {
    return packet << header.getWidth() << header.getHeight() << header.getSeed();
}

sf::Packet& operator>>(sf::Packet& packet, MapHeader& header) {
    int width, height, seed;
    packet >> width >> height >> seed;
    header.setWidth(width);
    header.setHeight(height);
    header.setSeed(seed);
    
    return packet;
}

MapHeader::MapHeader()
: MapHeader(0,0,0) {
}

MapHeader::MapHeader(int height, int width, double seed)
: m_height(height)
, m_width(width)
, m_seed(seed) {
}

MapHeader::~MapHeader() {
}

int MapHeader::getSize() const {
    return m_width * m_height;
}

int MapHeader::getWidth() const {
    return m_width;
}

int MapHeader::getHeight() const {
    return m_height;
}

void MapHeader::setSeed(int seed) {
    m_seed = seed;
}

void MapHeader::setWidth(int width) {
    m_width = width;
}

void MapHeader::setHeight(int height) {
    m_height = height;
}

int MapHeader::getSeed() const {
    return m_seed;
}