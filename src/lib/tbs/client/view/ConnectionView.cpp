/* 
 * File:   ConnectionView.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 11:24
 */

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "client/view/ConnectionView.h"

ConnectionView::ConnectionView(const std::string& ipAddressText)
: m_fixedTextView("Try to connect to", 60, Center)
, m_ipAddressText(ipAddressText) {

    // Set input text viewport
    m_ipAddressSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});
}

ConnectionView::~ConnectionView() {
}

void ConnectionView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    MenuView::draw(target, states);
    
    sf::View currentView = target.getView();

    TextView::setAbs(false);
    
    // Draw InputText
    target.setView(m_ipAddressSfView);
    target.draw(m_fixedTextView, states);
    target.draw(TextView(m_ipAddressText, 60, Center), states);

    target.setView(currentView);
}
