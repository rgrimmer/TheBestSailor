/* 
 * File:   Sail.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:37
 */

#ifndef SAIL_H
#define	SAIL_H

#include <SFML/System/Vector2.hpp>

class Sail {
public:
    Sail(float angle = 0.0f);
    virtual ~Sail();

    void update(float dt);

    void turnNegative(float angle = 5.0f);
    void turnPositive(float angle = 5.0f);
    bool isTurningPositive() const;
    bool isTurningNegative() const;
    void setTurningPositive(bool value);
    void setTurningNegative(bool value);
    
    void setAngle(float angle);
    float getAngle(void) const;

private:
    float m_angle;
    bool m_turnNegative;
    bool m_turnPositive;
};

#endif	/* SAIL_H */

