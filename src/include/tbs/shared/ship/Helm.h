/* 
 * File:   Helm.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:28
 */

#ifndef HELM_H
#define	HELM_H


class Helm {
public:
    Helm();
    virtual ~Helm();
    
    inline float& angle() { return m_angle; }
    inline float angle() const { return m_angle; }
    void turn(float angle);
    
    void update(float dt);
    
private:
    float m_angle;

};

#endif	/* HELM_H */

