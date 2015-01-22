/* 
 * File:   MenuView.h
 * Author: maxence
 *
 * Created on 22 janvier 2015, 12:32
 */

#ifndef MENUVIEW_H
#define	MENUVIEW_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

#include "client/view/BackgroundView.h"
#include "client/view/TextView.h"

class MenuView : public  sf::Drawable {
public:
    MenuView();
    virtual ~MenuView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    BackgroundView m_backgroundView;
    TextView m_titleView;

};

#endif	/* MENUVIEW_H */

