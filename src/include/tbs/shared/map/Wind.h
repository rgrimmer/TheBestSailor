/* 
 * File:   Wind.h
 * Author: maxence
 *
 * Created on 28 octobre 2014, 23:06
 */

#ifndef WIND_H
#define	WIND_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Wind : public sf::Drawable, public sf::Transformable {
public:
    static const int maxStrength;
    static const int minStrength;
    
    Wind();
    Wind(int strength, float direction);
    Wind(const Wind& orig);
    virtual ~Wind();
private:

    int m_strength;
    float m_direction;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray getVertices() const;


};

#endif	/* WIND_H */

