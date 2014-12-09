/* 
 * File:   GlobalView.h
 * Author: maxence
 *
 * Created on 7 décembre 2014, 11:54
 */

#ifndef GLOBALVIEW_H
#define	GLOBALVIEW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "shared/map/MapHeader.h"
#include "shared/map/HeigthMap.h"
//#include "sha"D

class GlobalView : public sf::Drawable {
public:
    GlobalView();
    virtual ~GlobalView();
    
    void loadInformation();
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    
    MapHeader *m_mapHeader;
    HeigthMap *m_heigthMap;
    
    sf::View m_worldView;
    sf::View m_informationView;
    sf::RenderTexture m_informationTexture;

    sf::Texture *m_background;
};

#endif	/* GLOBALVIEW_H */

