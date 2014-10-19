/* 
 * File:   Map.h
 * Author: maxence
 *
 * Created on 10 octobre 2014, 13:39
 */

#ifndef MAP_H
#define	MAP_H

#include <assert.h>
#include <SFML/Network/Packet.hpp>

#include "MapHeader.h"

class Map {
public:
    Map();
    Map(const MapHeader &header);
    virtual ~Map();

    
    float& operator()(int i, int j) {
        return m_container[i][j];
    }

    float operator()(int i, int j) const {
        return m_container[i][j];
    }
    
    int getSize() const;
    int getWidth() const;
    int getHeight() const;
    double getSeed() const;
    MapHeader getHeader() const;
    //void setHeader(const MapHeader& mapHeader);

private:
    MapHeader m_header;
    float** m_container;
};

#endif	/* MAP_H */

