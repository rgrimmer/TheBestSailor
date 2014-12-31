/* 
 * File:   ConnectionView.h
 * Author: maxence
 *
 * Created on 31 décembre 2014, 11:24
 */

#ifndef CONNECTIONVIEW_H
#define	CONNECTIONVIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "client/BackgroundView.h"

class ConnectionView : public sf::Drawable {
public:
    ConnectionView();
    virtual ~ConnectionView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
 
private:
    BackgroundView m_backgroundView;
//    sf::Text
};

#endif	/* CONNECTIONVIEW_H */

