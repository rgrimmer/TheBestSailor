/* 
 * File:   DetailsView.h
 * Author: maxence
 *
 * Created on 7 décembre 2014, 18:02
 */

#ifndef DETAILSVIEW_H
#define	DETAILSVIEW_H

#include <vector>
#include <SFML/Graphics/Drawable.hpp>

#include "shared/map/HeigthMap.h"
#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

#include "client/checkpoint/ClientCheckPointManager.h"
#include "client/map/HeigthMapView.h"
#include "client/map/WindMapView.h"
#include "client/ship/ShipView.h"
#include "ClientWorld.h"

class DetailsView : public sf::Drawable {
public:
    DetailsView(const ClientWorld &world);
    virtual ~DetailsView(void);

    sf::View& getView(void);
    bool switchEnableWind(void);
    bool switchSquared(void);
    void setCenter(const sf::Vector2f& center);
    void setSize(const sf::Vector2f& size);
    void updateShips(void);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // Graphic
    const ClientWorld& m_world;
    
    HeigthMapView m_heigthMapView;
    WindMapView m_windMapView;
    std::vector<ShipView> m_shipsView;
    
    sf::View m_currentView;
    bool m_followingCamera;

    // Enable
    bool m_enableWind;

};

#endif	/* DETAILSVIEW_H */

