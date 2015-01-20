/* 
 * File:   ConnectionView.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 11:24
 */

#include <SFML/Graphics/Text.hpp>

#include "shared/Font.h"

#include "client/view/TextView.h"
#include "client/view/ConnectionView.h"

ConnectionView::ConnectionView(const std::string& ipAddressText)
: m_titleSfText("The Best Sailor", 130, Center)
, m_fixedTextView("Try to connect to", 60, Center)
, m_ipAddressText(ipAddressText) {
    // Set text viewport
    m_titleView.setViewport({0.0f, 0.0f, 1.0f, 1.0f});

    // Set input text viewport
    m_ipAddressSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});
}

ConnectionView::~ConnectionView() {
}

void ConnectionView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View currentView = target.getView();

    // Draw background
    target.draw(m_backgroundView, states);

    // Draw Title
    target.setView(m_titleView);
    target.draw(m_titleSfText, states);

    TextView::setAbs(false);
    
    // Draw InputText
    target.setView(m_ipAddressSfView);
    target.draw(m_fixedTextView, states);
    target.draw(TextView(m_ipAddressText, 60, Center), states);

    target.setView(currentView);
}
