/* 
 * File:   DetailsView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 18:02
 */
#include "client/DisplayInfo.h"

#include "client/DetailsView.h"

DetailsView::DetailsView(const HeigthMap& heigthMap, const WindMap& windMap, const Ship& ship) 
: m_heigthMapView(heigthMap)
, m_windMapView(windMap)
, m_shipView(ship) 
, m_enableWind(true)
{

}

bool DetailsView::switchEnableWind() {
    m_enableWind = !m_enableWind;
    return m_enableWind;
}

bool DetailsView::switchSquared() {
    return m_heigthMapView.switchSquared();
}


DetailsView::~DetailsView() {
}

void DetailsView::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    sf::Clock clockDraw;
    sf::Time timeDrawHeightMap, timeDrawWindMap;
    
    // Draw heightMap
    clockDraw.restart();
    target.draw(m_heigthMapView, states);
    timeDrawHeightMap = clockDraw.getElapsedTime();
        
    // Draw Ship
    target.draw(m_shipView, states);
    
    // Draw Wind
    if(m_enableWind) {
        clockDraw.restart();
        target.draw(m_windMapView, states);
        timeDrawWindMap = clockDraw.getElapsedTime();
    }
    
    

    target.draw(DisplayInfo("Draw(ms)"));
    target.draw(DisplayInfo("HeightMap : " + std::to_string(timeDrawHeightMap.asMilliseconds())));
    target.draw(DisplayInfo("WindMap : " + std::to_string(timeDrawWindMap.asMilliseconds())));
    
}

