/* 
 * File:   WindMap.h
 * Author: maxence
 *
 * Created on 27 octobre 2014, 19:44
 */

#ifndef WINDMAP_H
#define	WINDMAP_H

#include "MapHeader.h"

class WindMap {
public:
    WindMap();
    WindMap(const MapHeader &header);
    virtual ~WindMap();

    
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

/*#include <SFML/Graphics/Drawable.hpp>

#include "MapHeader.h"
#include "shared/Force.h"
#include <SFML/System/Vector2.hpp>

class WindMap {
public:

    enum horizontalDir {
    };

    enum windDirection {
        //        north = 0x0,
        //        south = 0x1,
        //        east = 0x2,
        //        weast = 0x4,
        //        northEast = north | east,
        //        northWeast = north | weast,
        //        southEast = south | east,
        //        southWeast = south | weast
        north,
        south,
        east,
        weast,
        northEast,
        northWeast,
        southEast,
        southWeast
    };


    WindMap();
    WindMap(const MapHeader &header);
    virtual ~WindMap();
    
    //DrawWind& wind(int x, int y);
    //const DrawWind& wind(int x, int y) const;
    //DrawWind& wind(const sf::Vector2i &point);
    //const DrawWind& wind(const sf::Vector2i &point)const;
    //Force force(const sf::Vector2f &point);
private:

    MapHeader m_header;
    float m_windDirection;
    int m_windStrength;
    //DrawWind* m_winds;

};
*/

#endif	/* WINDMAP_H */

