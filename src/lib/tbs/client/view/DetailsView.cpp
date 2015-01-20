/* 
 * File:   DetailsView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 18:02
 */
#include "client/view/TextView.h"

#include "client/view/DetailsView.h"
#include "client/ClientWorld.h"

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

DetailsView::DetailsView(const ClientWorld &world)
: m_world(world)
, m_heigthMapView(world.getHeightMap())
, m_windMapView(world.getWindMap())
, m_enableWind(true) {


    for (auto& ship : world.getShips()) {
        if (&ship.second != &world.getClientShip()) {
            m_shipsView.emplace_back(ship.second, sf::Color(255, 0, 0, 100));
        }
        else {
            m_currentView.setCenter(world.getClientShip().kinematics().position());
        }
    }

    m_shipsView.emplace_back(world.getClientShip(), sf::Color(255, 0, 0, 255));
    m_currentView.setSize(sf::Vector2f(world.getMap().getHeader().getWidth(), world.getMap().getHeader().getHeight()));
    
}

DetailsView::~DetailsView() {
}

bool DetailsView::switchEnableWind() {
    m_enableWind = !m_enableWind;
    return m_enableWind;
}

bool DetailsView::switchSquared() {
    return m_heigthMapView.switchSquared();
}

sf::View& DetailsView::getView() {
    return m_currentView;
}

void DetailsView::setCenter(const sf::Vector2f& center) {
    m_currentView.setCenter(center);
}

void DetailsView::setSize(const sf::Vector2f& size) {
    m_currentView.setSize(size);
}

void DetailsView::updateShips(void) {
    m_shipsView.clear();
    for (auto& ship : m_world.getShips()) {
        m_shipsView.emplace_back(ship.second);
    }
}

void DetailsView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View viewCpy = target.getView();
    target.setView(m_currentView);

    sf::Clock clockDraw;
    sf::Time timeDrawHeightMap, timeDrawWindMap;

    // Draw heightMap
    target.draw(m_heigthMapView, states);
    timeDrawHeightMap = clockDraw.restart();

    // Draw checkpoints
    for (auto& checkPoint : m_world.getCheckPointManager().getCheckPoints()) {
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

    /*TextView::update();
    TextView::setAbs(true);
    
    target.draw(TextView("Draw(ms)"));
    target.draw(TextView("HeightMap : " + std::to_string(timeDrawHeightMap.asMilliseconds())));
    target.draw(TextView("WindMap : " + std::to_string(timeDrawWindMap.asMilliseconds())));
     */
    
    target.setView(viewCpy);
}

