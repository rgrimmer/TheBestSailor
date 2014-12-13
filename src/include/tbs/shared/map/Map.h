/* 
 * File:   Map.h
 * Author: maxence
 *
 * Created on 13 décembre 2014, 11:48
 */

#ifndef MAP_H
#define	MAP_H

#include <SFML/Network/Packet.hpp>

#include "MapHeader.h"
#include "HeigthMap.h"
#include "WindMap.h"

class Map {
public:
    Map();
    Map(const MapHeader &m_header);
    virtual ~Map();

    const MapHeader& getHeader() const;
    const HeigthMap& getHeightMap() const;
    const WindMap& getWindMap() const;
    MapHeader& getHeader();
    HeigthMap& getHeightMap();
    WindMap& getWindMap();

private:
    MapHeader m_header;
    HeigthMap m_heightMap;
    WindMap m_windMap;

};

sf::Packet& operator<<(sf::Packet& packet, const Map& map);

#endif	/* MAP_H */
