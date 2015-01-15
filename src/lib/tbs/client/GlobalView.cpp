/* 
 * File:   GlobalView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 11:54
 */

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>

#include "shared/Utils.h"
#include "shared/map/MapHeader.h"
//#include "shared/map/HeigthMap.h"
//#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

#include "client/TextView.h"
#include "client/GlobalView.h"

GlobalView::GlobalView(const HeigthMap& heigthMap, const WindMap& windMap, const Ship& ship)
: m_titleSfText("The Best Sailor", 130, Center)
, m_mapHeader(heigthMap.getHeader())
, m_heigthMapView(heigthMap)
, m_windMapView(windMap)
, m_shipView(ship) {
    // Set title view
    m_titleView.setViewport(sf::FloatRect(0.01f, 0.0f, 1.0f, 1.0f));

    // Set world view
    m_worldViewUnit = sf::View(sf::FloatRect(0.0f, 0.0f, m_mapHeader.getWidth(), m_mapHeader.getHeight()));

    // Set viewport for the view
    float leftMargin = 0.01f;
    sf::FloatRect worldViewport(leftMargin, 0.2f, 0.6f, 0.79f);
    m_worldViewUnit.setViewport(worldViewport);

    // Set info view
    float leftInfo = worldViewport.left + worldViewport.width + leftMargin;
    float topInfo = worldViewport.top;
    float widthInfo = 1 - leftInfo - leftMargin;
    float heightInfo = worldViewport.height;
    m_infoView.setViewport(sf::FloatRect(leftInfo, topInfo, widthInfo, heightInfo));
}

GlobalView::~GlobalView() {

}

void GlobalView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Save current view state
    sf::View curView = target.getView();

    // Draw background
    target.draw(m_backgroundView);

    // Draw title
    target.setView(m_titleView);
    target.draw(m_titleSfText);

    // Draw world in worldView
    target.setView(m_worldViewUnit);
    target.draw(m_heigthMapView, states);

    // Set ship on view
    sf::CircleShape shipShape(1.0f);
    shipShape.setPosition(m_shipView.getShip().kinematics().position());
    target.draw(shipShape);

    // Draw info
    TextView::setAbs(false);
    target.setView(m_infoView);
    target.draw(TextView("Information", 60, TypeAlign::Center, sf::Text::Underlined));
    target.draw(TextView("Position", 40, TypeAlign::Regular, sf::Text::Italic));
    target.draw(TextView("x : " + std::to_string(m_shipView.getShip().kinematics().position().x) + "\ny : " + std::to_string(m_shipView.getShip().kinematics().position().y)));

    // Reset normal view
    target.setView(curView);
}
