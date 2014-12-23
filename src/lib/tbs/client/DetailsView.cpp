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

DetailsView::DetailsView(const ClientWorld &world, const HeigthMap& heigthMap, const WindMap& windMap, const Ship& ship)
: m_world(world)
, m_heigthMapView(heigthMap)
, m_windMapView(windMap)
, m_shipView(ship)
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
    
    const sf::Vector2f& shipPos = m_shipView.getShip().kinematics().position();

    //Draw vector
    sf::Vector2f windV, aWind, P, F, FM;
    m_world.getShipVelocity(windV, aWind, P, F, FM);
    target.draw(VectorView(shipPos, windV, "Wind", sf::Color::White));
    target.draw(VectorView(shipPos, aWind, "Wa", sf::Color::Blue));
    target.draw(VectorView(shipPos, P, "P", sf::Color::Cyan));
    target.draw(VectorView(shipPos, F, "F", sf::Color::Green));
    target.draw(VectorView(shipPos, FM, "Fm", sf::Color::Magenta));

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
    target.draw(DisplayInfo("WindMap : " + std::to_string(timeDrawWindMap.asMilliseconds())));
    Wind wind = m_world.getMap().getWind(static_cast<sf::Vector2i> (m_world.getShip().kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));
    target.draw(DisplayInfo("Wind(f:" + std::to_string(wind.force()) + ".d:" + std::to_string(wind.direction()) + ")"));
    if (m_world.windComeFromFront(wind))
        target.draw(DisplayInfo("Wind come from front"));
    else
        target.draw(DisplayInfo("Wind come from back"));
    if (m_world.windComeFromTribord(wind))
        target.draw(DisplayInfo("Wind come from tribord"));
    else
        target.draw(DisplayInfo("Wind come from babord"));
    target.draw(DisplayInfo("Wind " + std::to_string(windV.x) + " " + std::to_string(windV.y)));
    target.draw(DisplayInfo("shipAngle " + std::to_string(m_world.getShip().getAngle())));
}

