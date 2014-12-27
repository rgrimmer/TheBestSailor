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
    Sail();
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
    bool m_turnPositive;
    bool m_turnNegative;

    float m_angle;
};

#endif	/* SAIL_H */

