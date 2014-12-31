/* 
 * File:   ConnectionView.h
 * Author: maxence
 *
 * Created on 31 décembre 2014, 11:24
 */

#ifndef CONNECTIONVIEW_H
#define	CONNECTIONVIEW_H

#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "client/BackgroundView.h"
#include "DisplayInfo.h"

class ConnectionView : public sf::Drawable {
public:
    ConnectionView(const std::string& ipAddressText);
    virtual ~ConnectionView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
 
private:
    BackgroundView m_backgroundView;

    sf::View m_titleView;
    DisplayInfo m_titleSfText;
    
    sf::View m_ipAddressSfView;
    DisplayInfo m_fixedTextView;
    DisplayInfo m_ipAddressView;
};

#endif	/* CONNECTIONVIEW_H */

