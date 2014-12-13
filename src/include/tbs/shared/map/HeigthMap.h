/* 
 * File:   HeigthMap.h
 * Author: maxence
 *
 * Created on 10 octobre 2014, 13:39
 */

#ifndef HEIGHTMAP_H
#define	HEIGHTMAP_H

#include <SFML/Network/Packet.hpp>

#include "MapHeader.h"

class HeigthMap {
public:
    HeigthMap();
    HeigthMap(const MapHeader &header);
    virtual ~HeigthMap();

    float& operator()(int i, int j) {
        return m_container[i][j];
    }

    float operator()(int i, int j) const {
        return m_container[i][j];
    }

    int getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getSeed() const;
    const MapHeader& getHeader() const;
    MapHeader& getHeader();
    //void setHeader(const MapHeader& mapHeader);

private:
    MapHeader m_header;
    float** m_container;
};

sf::Packet& operator <<(sf::Packet& packet, const HeigthMap& map);

#endif	/* HEIGHTMAP_H */

