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
    HeigthMap(const HeigthMap& other);
    
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
    float getValue(int x, int y) const;

private:
    MapHeader m_header;
    std::vector<std::vector<float> > m_container;
//    float** m_container;
};

sf::Packet& operator <<(sf::Packet& packet, const HeigthMap& map);

#endif	/* HEIGHTMAP_H */

