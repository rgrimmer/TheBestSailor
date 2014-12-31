/* 
 * File:   GlobalView.h
 * Author: maxence
 *
 * Created on 7 décembre 2014, 11:54
 */

#ifndef GLOBALVIEW_H
#define	GLOBALVIEW_H

#include <string>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "client/DisplayInfo.h"
#include "client/BackgroundView.h"
#include "client/map/HeigthMapView.h"
#include "client/map/WindMapView.h"
#include "client/ship/ShipView.h"

class MapHeader;
class HeigthMap;
class WindMap;
class Ship;

class GlobalView : public sf::Drawable {
public:
    GlobalView(const HeigthMap& heigthMap, const WindMap& windMap, const Ship& ship);
    virtual ~GlobalView();
    
    void loadInformation();
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Background
    BackgroundView m_backgroundView;
    
    // Title
    sf::View m_titleView;
    DisplayInfo m_titleSfText;
    
    // World
    const MapHeader &m_mapHeader;
    
    // Graphic world
    HeigthMapView m_heigthMapView;
    WindMapView m_windMapView;
    ShipView m_shipView;
    
    // ClientWorld
    sf::View m_worldViewGraphic;
    sf::View m_worldViewUnit;
    
    // Info
    sf::View m_infoView;

};

#endif	/* GLOBALVIEW_H */

