/* 
 * File:   WindMap.h
 * Author: maxence
 *
 * Created on 27 octobre 2014, 19:44
 */

#ifndef WINDMAP_H
#define	WINDMAP_H

#include <SFML/System/Vector2.hpp>
#include "MapHeader.h"
#include "Wind.h"

class WindMap {
public:
    static const int maxStrength;
    static const int minStrength;

    WindMap();
    WindMap(const MapHeader &header);
    virtual ~WindMap();

    Wind& wind(int i, int j) {
        return m_container[i][j];
    }

    Wind wind(int i, int j) const {
        return m_container[i][j];
    }

    Wind& wind(const sf::Vector2i &position) {
        return m_container[position.x][position.y];
    }

    Wind wind(const sf::Vector2i &position) const {
        return m_container[position.x][position.y];
    }

    int getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getSeed() const;
    const MapHeader& getHeader() const;
    MapHeader& getHeader();

private:
    MapHeader m_header;
    std::vector<std::vector<Wind> > m_container;
};

sf::Packet& operator<<(sf::Packet& packet, const WindMap& map);

#endif	/* WINDMAP_H */

