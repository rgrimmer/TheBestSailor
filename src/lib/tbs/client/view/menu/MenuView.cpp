/* 
 * File:   MenuView.cpp
 * Author: maxence
 * 
 * Created on 22 janvier 2015, 12:32
 */

#include "client/view/menu/MenuView.h"

MenuView::MenuView()
: m_titleView("The Best Sailor", 130, Center) {
}

MenuView::~MenuView() {
}

void MenuView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw background
    target.draw(m_backgroundView, states);

    // Draw Title
    target.draw(m_titleView, states);
}
