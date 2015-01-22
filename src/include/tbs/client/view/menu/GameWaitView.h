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

    void setLeftTime(float leftTime);
    void decreaseLeftTime(float leftTime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void updateText();
    
private:
    sf::View m_centerSfView;
    std::string m_leftTimeText;
    float m_leftTime;

};

#endif	/* GAMEWAITVIEW_H */

