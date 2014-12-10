
#ifndef HEIGTHMAPVIEW_H
#define	HEIGTHMAPVIEW_H

#include <SFML/Graphics.hpp>
#include "shared/Utils.h"
#include "shared/map/HeigthMap.h"

class HeigthMapView : public sf::Drawable {
    
public:
    HeigthMapView(const HeigthMap &heigthMap);
    bool switchSquared();

private:

    void load();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Model 
    const HeigthMap &m_heigthMap;
    
    // Graphic 
    bool m_squared;
    sf::VertexArray m_vertices;
};

#endif