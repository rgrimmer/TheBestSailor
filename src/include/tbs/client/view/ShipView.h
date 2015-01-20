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


class Ship;
class VectorView;

class ShipView : public sf::Drawable {
public:
    ShipView(const Ship &ship, const sf::Color & color = sf::Color::Red);
    ShipView(const ShipView& other);

    virtual ~ShipView();

    const Ship& getShip() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Model
    const Ship& m_ship;

    // Graphic
    VectorView* m_speedView;
    VectorView* m_accView;
    
    sf::Sprite m_boatSprite;
    sf::RectangleShape m_sailShape;
    static sf::Texture g_texture;

};


#endif	/* SHIPVIEW_H */

