/* 
 * File:   MapHeader.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 16:23
 */

#ifndef MAPHEADER_H
#define	MAPHEADER_H

class MapHeader {
public:
    MapHeader();
    MapHeader(int heigth, int width, double seed = 0);
    MapHeader(const MapHeader& orig);
    virtual ~MapHeader();
    
    int getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getSeed() const;
    
private:
    int m_height;
    int m_width;
    double m_seed;
};

#endif	/* MAPHEADER_H */

