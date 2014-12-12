/* 
 * File:   DrawShip.h
 * Author: maxence
 *
 * Created on 29 novembre 2014, 10:43
 */

#ifndef SHIPVIEW_H
#define	SHIPVIEW_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "shared/ship/Ship.h"
#include "client/VectorView.h"

class ShipView : public sf::Drawable, public sf::Transformable {
public:
    ShipView(const Ship &ship);
    virtual ~ShipView();

    inline const Ship& getShip() const { return m_ship; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Model
    const Ship& m_ship;

    // Graphic
    sf::RectangleShape m_shipShape;
    VectorView<float>* m_speedView;
    VectorView<float>* m_accView;


};

#endif	/* SHIPVIEW_H */

