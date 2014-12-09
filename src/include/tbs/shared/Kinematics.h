/* 
 * File:   Kinematics.h
 * Author: maxence
 *
 * Created on 1 novembre 2014, 09:16
 */

#ifndef KINEMATICS_H
#define	KINEMATICS_H

#include <cmath>
#include <SFML/System/Vector2.hpp>

class Kinematics {
public:
    Kinematics();
    virtual ~Kinematics();
    template <typename T>
    static T degToRad(T deg) { return deg / 180.0 * M_PI; }
    template <typename T>
    static T radToDeg(T rad) { return rad * 180.0 / M_PI; }
    template <typename T>
    static float norme(const sf::Vector2<T> &vector) {return std::sqrt(vector.x * vector.x + vector.y * vector.y);}
    template <typename T>
    static T direction(const sf::Vector2<T> &vector) { 
        float deg = Kinematics::radToDeg(std::atan(vector.y/vector.x));
        if(std::signbit(vector.x))
            deg += 180.0f;
        else
            if(std::signbit(vector.y))
                deg += 360.0f;
        return deg;
    }
    
    static sf::Vector2f vectorDir(float angle);
//    static sf::Vector2f pourcentage(const sf::Vector2f &vector);
    
    inline sf::Vector2f& acceleration(void) { return m_acceleration; }
    inline const sf::Vector2f& acceleration(void) const { return m_acceleration; }
    inline sf::Vector2f& speed(void) { return m_speed; }
    inline const sf::Vector2f& speed(void) const { return m_speed; }
    inline  sf::Vector2f& position(void) { return m_position; }
    inline const sf::Vector2f& position(void) const { return m_position; }
    float direction(void) const;
    
    void update(float dt);

private:
    sf::Vector2f m_acceleration;
    sf::Vector2f m_speed;
    sf::Vector2f m_position;

};

#endif	/* KINEMATICS_H */

