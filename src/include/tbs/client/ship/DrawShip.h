/* 
 * File:   DrawShip.h
 * Author: maxence
 *
 * Created on 29 novembre 2014, 10:43
 */

#ifndef DRAWSHIP_H
#define	DRAWSHIP_H

#include "shared/ship/Ship.h"
#include "client/VectorView.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class DrawShip : public sf::Drawable, public sf::Transformable {
public:
    DrawShip();
    virtual ~DrawShip();
    
    void load(const Ship &ship);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // Model
    const Ship *m_ship;

    // Graphic
    sf::RectangleShape m_shipView;
    VectorView<float>* m_speedView;
    VectorView<float>* m_accView;


};

#endif	/* DRAWSHIP_H */

