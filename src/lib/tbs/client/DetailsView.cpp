/* 
 * File:   DetailsView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 18:02
 */
#include "client/TextView.h"

#include "client/DetailsView.h"
#include "client/ClientWorld.h"

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

DetailsView::DetailsView(const ClientWorld &world)
: m_world(world)
, m_heigthMapView(world.getHeightMap())
, m_windMapView(world.getWindMap())
//, m_checkPointManager(world.getCheckPointManager())
, m_enableWind(true) {

    for (auto& ship : world.getShips()) {
        m_shipsView.emplace_back(ship.second);
    }
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

void DetailsView::updateShips(void) {
    m_shipsView.clear();
    for (auto& ship : m_world.getShips()) {
        m_shipsView.emplace_back(ship.second);
    }
}

void DetailsView::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    sf::Clock clockDraw;
    sf::Time timeDrawHeightMap, timeDrawWindMap;

    // Draw heightMap
    target.draw(m_heigthMapView, states);
    timeDrawHeightMap = clockDraw.restart();

    // Draw checkpoints
    std::cout << m_world.getCheckPointManager().getCheckPointCount() << std::endl;
    for(auto& checkPoint : m_world.getCheckPointManager().getCheckPoints()) {
        target.draw(checkPoint, states);
    }
    
    // Draw Ships
    for (auto& shipView : m_shipsView)
        target.draw(shipView, states);

    // Draw Wind
    if (m_enableWind) {
        target.draw(m_windMapView, states);
        timeDrawWindMap = clockDraw.restart();
    }
    
    TextView::update();
    TextView::setAbs(true);
    target.draw(TextView("Draw(ms)"));
    target.draw(TextView("HeightMap : " + std::to_string(timeDrawHeightMap.asMilliseconds())));
    target.draw(TextView("WindMap : " + std::to_string(timeDrawWindMap.asMilliseconds())));
}

