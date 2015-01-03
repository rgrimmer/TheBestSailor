/* 
 * File:   ClientCheckPoint.h
 * Author: remy
 *
 * Created on 2 janvier 2015, 21:37
 */

#ifndef CLIENTCHECKPOINT_H
#define	CLIENTCHECKPOINT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>

class ClientCheckPoint : public sf::Drawable{
public:
    explicit ClientCheckPoint(sf::Vector2i position);
    virtual ~ClientCheckPoint();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Vector2i m_position;
    sf::RectangleShape m_shape;
};

#endif	/* CLIENTCHECKPOINT_H */

