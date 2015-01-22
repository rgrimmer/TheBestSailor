/* 
 * File:   GameWaitView.cpp
 * Author: maxence
 * 
 * Created on 22 janvier 2015, 13:00
 */

#include "client/view/menu/GameWaitView.h"

GameWaitView::GameWaitView()
: m_centerFixedTextView("Wait", 60, Center) {
    
    // Set center text viewport
    m_centerSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});
    
}

GameWaitView::~GameWaitView() {
}

void GameWaitView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    MenuView::draw(target, states);
    
    sf::View currentView = target.getView();

    TextView::setAbs(false);
    
    // Draw InputText
    target.setView(m_centerSfView);
    target.draw(m_centerFixedTextView, states);

    target.setView(currentView);
}

