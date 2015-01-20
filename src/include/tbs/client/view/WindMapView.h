/* 
 * File:   Wind.h
 * Author: maxence
 *
 * Created on 28 octobre 2014, 23:06
 */

#ifndef WINDMAPVIEW_H
#define	WINDMAPVIEW_H

#include <SFML/Graphics.hpp>
#include "shared/Utils.h"
#include "shared/map/WindMap.h"

class WindMapView : public sf::Drawable, public sf::Transformable {
    
public:
    WindMapView(const WindMap& windMap);


    void load();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Model
    const WindMap& m_windMap;
    
    // Graphic
    sf::VertexArray m_vertices;
};

#endif	/* DRAWWIND_H */

