/* 
 * File:   DetailsView.h
 * Author: maxence
 *
 * Created on 7 décembre 2014, 18:02
 */

#ifndef DETAILSVIEW_H
#define	DETAILSVIEW_H

#include <SFML/Graphics/Drawable.hpp>

#include "shared/map/HeigthMap.h"
#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

#include "client/map/HeigthMapView.h"
#include "client/map/WindMapView.h"
#include "client/ship/ShipView.h"
#include "ClientWorld.h"

class DetailsView : public sf::Drawable {
public:
    DetailsView(const ClientWorld &world, const HeigthMap &heigthMap, const WindMap &windMap, const Ship &ship);
    virtual ~DetailsView();

    bool switchEnableWind();
    bool switchSquared();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // Graphic
    const ClientWorld& m_world;
    HeigthMapView m_heigthMapView;
    WindMapView m_windMapView;
    ShipView m_shipView;

    // Enable
    bool m_enableWind;

};

#endif	/* DETAILSVIEW_H */

