/* 
 * File:   GlobalView.h
 * Author: maxence
 *
 * Created on 7 décembre 2014, 11:54
 */

#ifndef GLOBALVIEW_H
#define	GLOBALVIEW_H

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "shared/map/MapHeader.h"
#include "shared/map/HeigthMap.h"
#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

#include "client/map/HeigthMapView.h"
#include "client/map/WindMapView.h"
#include "client/ship/ShipView.h"
#include "DisplayInfo.h"

//#include "sha"D

class GlobalView : public sf::Drawable {
public:
    GlobalView(const HeigthMap& heigthMap, const WindMap& windMap, const Ship& ship);
    virtual ~GlobalView();
    
    void loadInformation();
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    
    const MapHeader &m_mapHeader;
    
    // Graphic
    HeigthMapView m_heigthMapView;
    WindMapView m_windMapView;
    ShipView m_shipView;
    
    // Title
    sf::View m_titleView;
    DisplayInfo m_titleSfText;
    
    // World
    sf::View m_worldViewGraphic;
    sf::View m_worldViewUnit;
    
    // Info
    sf::View m_infoView;

    // Background
    sf::View m_backgroundView;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_background;
};

#endif	/* GLOBALVIEW_H */

