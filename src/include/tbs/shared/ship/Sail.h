/* 
 * File:   Sail.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:37
 */

#ifndef SAIL_H
#define	SAIL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Sail : public sf::Drawable {
public:
    Sail();
    virtual ~Sail();
    
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float getAngleWith(const sf::Vector2f &direction) { return 10; }
private:

public:

    void setPosition(const sf::Vector2f & pos);
    void setAngle(float angle);
    float getAngle(void) const;
    
private:
    sf::RectangleShape m_line;
    float m_angle;
    sf::Vector2f m_position;
};

#endif	/* SAIL_H */

