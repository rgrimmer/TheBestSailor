/* 
 * File:   MapHeader.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 16:23
 */

#ifndef MAPHEADER_H
#define	MAPHEADER_H

#include <SFML/Network/Packet.hpp>

class MapHeader {
public:
    MapHeader();
    MapHeader(int heigth, int width, double seed = 0);
    virtual ~MapHeader();

    int getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getSeed() const;

    void setSeed(int seed);
    void setWidth(int width);
    void setHeight(int height);

private:
    int m_height;
    int m_width;
    double m_seed;
};

#endif	/* MAPHEADER_H */

