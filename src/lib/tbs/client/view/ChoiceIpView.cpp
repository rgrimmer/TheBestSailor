/* 
 * File:   ChoiceIpView.cpp
 * Author: maxence
 * 
 * Created on 16 janvier 2015, 20:08
 */
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Time.hpp>

#include "client/view/ChoiceIpView.h"

ChoiceIpView::ChoiceIpView(const std::string& ipAddressText)
: m_titleSfText("The Best Sailor", 130, Center)
, m_ipAddressText(ipAddressText)
, m_fixedTextView1("Enter the server ip :", 60, Center)
, m_fixedTextView2("Public IP : " + sf::IpAddress::getPublicAddress(sf::milliseconds(500)).toString(), 40)
, m_fixedTextView3("Local IP : " + sf::IpAddress::getLocalAddress().toString(), 40) {
    // Set text viewport
    m_titleView.setViewport({0.0f, 0.0f, 1.0f, 1.0f});

    // Set input text viewport
    m_ipEnterSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});
    
    // Set info text viewport
    m_ipInfoSfView.setViewport({0.0f, 0.9f, 1.0f, 1.0f});
}

ChoiceIpView::~ChoiceIpView() {
}

void ChoiceIpView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View currentView = target.getView();

    // Draw background
    target.draw(m_backgroundView);

    // Draw Title
    target.setView(m_titleView);
    target.draw(m_titleSfText);
    
    TextView::setAbs(false);

    // Draw InputText
    target.setView(m_ipEnterSfView);
    target.draw(m_fixedTextView1);
    target.draw(TextView(m_ipAddressText, 60, Center));
    
    // Draw InfoText
    target.setView(m_ipInfoSfView);
    target.draw(m_fixedTextView2);
    target.draw(m_fixedTextView3);

    target.setView(currentView);
}
