/* 
 * File:   Ship.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:34
 */

#ifndef SHIP_H
#define	SHIP_H

#include "Helm.h"
#include "Sail.h"
#include "shared/Kinematics.h"

class Ship {
public:
    static const int maxType;
    static const int TurnVelocity;
    
public:
    Ship(const sf::Vector2f& position = {0,0}, float shipAngle = 0, float sailAngle = 0, int type = 0);
    virtual ~Ship();
    
    Sail& getSail();
    const Sail& getSail() const;

    void setAngle(float angle);
    float getAngle(void) const;
    
    int getType() const;
    float getDirection() const;
    sf::Vector2f& position();
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f& velocity();
    const sf::Vector2f& getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);
    void setType(int type);
    
    
    void turnPositive(float dt);
    void turnNegative(float dt);
    bool isTurningPositive() const;
    bool isTurningNegative() const;
    void setTurningPositive(bool value);
    void setTurningNegative(bool value);

    void initialize(const sf::Vector2f & position, const sf::Vector2f & speed);
    void update(float dt);


private:
    // Ship state
    bool m_turnPositive;
    bool m_turnNegative;
    float m_angle;
    int m_type;
    
    // Ship kinematics
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    
    Sail m_sail;


};

#endif	/* SHIP_H */

