/* 
 * File:   GlobalView.cpp
 * Author: maxence
 * 
 * Created on 7 décembre 2014, 11:54
 */


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

#include "shared/Utils.h"

#include "client/GlobalView.h"
#include "client/DisplayInfo.h"

GlobalView::GlobalView(const HeigthMap& heigthMap, const WindMap& windMap, const Ship& ship)
: m_mapHeader(heigthMap.getHeader())
, m_heigthMapView(heigthMap)
, m_windMapView(windMap)
, m_shipView(ship)
, m_titleSfText("The Best Sailor", 130, Center) {
    // Set title view
    m_titleView.setViewport(sf::FloatRect(0.01f, 0.0f, 1.0f, 1.0f));

    // Set world view
    m_worldViewGraphic = sf::View(sf::FloatRect(0.0f, 0.0f, m_mapHeader.getWidth() * TILE_SIZE, m_mapHeader.getHeight() * TILE_SIZE));
    m_worldViewUnit = sf::View(sf::FloatRect(0.0f, 0.0f, m_mapHeader.getWidth(), m_mapHeader.getHeight()));

    // Set viewport for the view
    float leftMargin = 0.01f;
    sf::FloatRect worldViewport(leftMargin, 0.2f, 0.6f, 0.79f);
    m_worldViewGraphic.setViewport(worldViewport);
    m_worldViewUnit.setViewport(worldViewport);

    // Set info view
    float leftInfo = worldViewport.left + worldViewport.width + leftMargin;
    float topInfo = worldViewport.top;
    float widthInfo = 1 - leftInfo - leftMargin;
    float heightInfo = worldViewport.height;
    m_infoView.setViewport(sf::FloatRect(leftInfo, topInfo, widthInfo, heightInfo));

    // Set background view
    if (!m_backgroundTexture.loadFromFile("share/tbs/textures/wood1.png")) {
        std::cout << "Impossible de charger la texture de background";
    }
    m_background.setTexture(m_backgroundTexture);
    m_backgroundView = sf::View(sf::FloatRect(0.0f, 0.0f, m_backgroundTexture.getSize().x, m_backgroundTexture.getSize().y));
}

GlobalView::~GlobalView() {

}
#include <SFML/Graphics/RenderStates.hpp>

void GlobalView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Save current view state
    sf::View curView = target.getView();

    // Draw background on static view
    target.setView(m_backgroundView);
    target.draw(m_background);

    // Draw title
    target.setView(m_titleView);
    target.draw(m_titleSfText);

    // Draw world in worldView
    target.setView(m_worldViewGraphic);
    target.draw(m_heigthMapView, states);

    // Set ship on view
    target.setView(m_worldViewUnit);
    sf::CircleShape ship(1.0f);
    //    ship.setOrigin(0.5f, 0.5f);
    const sf::Vector2f &shipPosView = m_shipView.getShip().kinematics().position();
    ship.setPosition(shipPosView.x / TILE_SIZE, shipPosView.y / TILE_SIZE);
    target.draw(ship);

    // Draw info
    DisplayInfo::setAbs(false);
    target.setView(m_infoView);
    target.draw(DisplayInfo("Information", 60, TypeAlign::Center, sf::Text::Underlined));
    target.draw(DisplayInfo("Position", 40, TypeAlign::Regular, sf::Text::Italic));
    target.draw(DisplayInfo("x : " + std::to_string(m_shipView.getShip().kinematics().position().x) + "\ny : " + std::to_string(m_shipView.getShip().kinematics().position().y)));

    // Reset normal view
    target.setView(curView);
}
