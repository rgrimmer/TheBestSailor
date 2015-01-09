/* 
 * File:   ConnectionView.cpp
 * Author: maxence
 * 
 * Created on 31 décembre 2014, 11:24
 */

#include <SFML/Graphics/Text.hpp>

#include "shared/Font.h"

#include "client/TextView.h"
#include "client/ConnectionView.h"

ConnectionView::ConnectionView(const std::string& ipAddressText)
: m_titleSfText("The Best Sailor", 130, Center)
, m_fixedTextView("IP address : ", 60, Center)
, m_ipAddressText(ipAddressText) {
    m_titleView.setViewport(sf::FloatRect(0.01f, 0.0f, 1.0f, 1.0f));

    // Set input text view
    m_ipAddressSfView.setViewport({0, 0, 1.0f, 1.0f});
}

ConnectionView::~ConnectionView() {
}

void ConnectionView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View currentView = target.getView();

    // Draw background
    target.draw(m_backgroundView);

    // Draw Title
    target.draw(m_titleSfText);

    // Draw InputText
    target.setView(m_ipAddressSfView);
    target.draw(m_fixedTextView);
    target.draw(TextView(m_ipAddressText, 60, Center));

    target.setView(currentView);
}
