/* 
 * File:   GameWaitView.h
 * Author: maxence
 *
 * Created on 22 janvier 2015, 13:00
 */

#ifndef GAMEWAITVIEW_H
#define	GAMEWAITVIEW_H

#include <SFML/Graphics/View.hpp>

#include "client/view/menu/MenuView.h"

class GameWaitView : public MenuView {
public:
    GameWaitView();
    virtual ~GameWaitView();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::View m_centerSfView;
    TextView m_centerFixedTextView;

};

#endif	/* GAMEWAITVIEW_H */

