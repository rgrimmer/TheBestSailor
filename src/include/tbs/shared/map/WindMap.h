/* 
 * File:   WindMap.h
 * Author: maxence
 *
 * Created on 27 octobre 2014, 19:44
 */

#ifndef WINDMAP_H
#define	WINDMAP_H

#include <SFML/Graphics/Drawable.hpp>

#include "MapHeader.h"
#include "Wind.h"
#include "shared/Force.h"
#include <SFML/System/Vector2.hpp>

class WindMap : public sf::Drawable {
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
    
    Wind& wind(int x, int y);
    const Wind& wind(int x, int y) const;
    Wind& wind(const sf::Vector2i &point);
    const Wind& wind(const sf::Vector2i &point)const;
    Force force(const sf::Vector2f &point);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    MapHeader m_header;
    float m_windDirection;
    int m_windStrength;
    Wind* m_winds;

};

#endif	/* WINDMAP_H */

