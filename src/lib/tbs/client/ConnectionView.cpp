/* 
 * File:   ConnectionView.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 11:24
 */

#include "client/ConnectionView.h"

ConnectionView::ConnectionView() {
}

ConnectionView::~ConnectionView() {
}

void ConnectionView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw background
    target.draw(m_backgroundView);
    
    // Draw Text
}
