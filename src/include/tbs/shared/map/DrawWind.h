/* 
 * File:   Wind.h
 * Author: maxence
 *
 * Created on 28 octobre 2014, 23:06
 */

#ifndef WIND_H
#define	WIND_H

#include <SFML/Graphics.hpp>
#include "shared/Utils.h"
#include "shared/map/WindMap.h"

class DrawWind : public sf::Drawable, public sf::Transformable {
    
public:

    void load(const WindMap &map);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
};

#endif	/* WIND_H */

