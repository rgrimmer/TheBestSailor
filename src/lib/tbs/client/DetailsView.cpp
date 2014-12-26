/* 
 * File:   DetailsView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 18:02
 */
#include "client/DisplayInfo.h"

#include "client/DetailsView.h"
#include "client/ClientWorld.h"

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

DetailsView::DetailsView(const ClientWorld &world)
: m_world(world)
, m_heigthMapView(world.getHeightMap())
, m_windMapView(world.getWindMap())
, m_shipView(world.getClientShip())
, m_enableWind(true) {

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
    target.draw(m_heigthMapView, states);
    timeDrawHeightMap = clockDraw.restart();

    // Draw Ship
    target.draw(m_shipView, states);
    clockDraw.restart();

    // Draw Wind
    if (m_enableWind) {
        target.draw(m_windMapView, states);
        timeDrawWindMap = clockDraw.restart();
    }
    DisplayInfo::update();
    DisplayInfo::setAbs(true);
    target.draw(DisplayInfo("Draw(ms)"));
    target.draw(DisplayInfo("HeightMap : " + std::to_string(timeDrawHeightMap.asMilliseconds())));
    target.draw(DisplayInfo("WindMap : " + std::to_string(timeDrawWindMap.asMilliseconds())));
}

