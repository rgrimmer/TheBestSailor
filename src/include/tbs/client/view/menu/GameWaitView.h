/* 
 * File:   GameWaitView.h
 * Author: maxence
 *
 * Created on 22 janvier 2015, 13:00
 */

#ifndef GAMEWAITVIEW_H
#define	GAMEWAITVIEW_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "shared/ship/Ship.h"

#include "client/view/menu/MenuView.h"

class GameWaitView : public MenuView {
public:
    GameWaitView();
    virtual ~GameWaitView();

    void setTimeLeft(float timeLeft);
    void decreaseTimeLeft(float dt);
    
    void setType(int shipType);

    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void updateText();
    
private:
    sf::View m_centerSfView;
    std::string m_leftTimeText;
    float m_timeLeft;

    sf::View m_shipSfView;
    sf::Texture m_shipTexture;
    sf::VertexArray m_shapeShip;
    sf::FloatRect m_shapeShipRect;
    
    int m_prevTexture;
};

#endif	/* GAMEWAITVIEW_H */

