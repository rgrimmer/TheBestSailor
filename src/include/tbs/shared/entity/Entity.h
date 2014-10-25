/* 
 * File:   Entity.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 15:21
 */

#ifndef ENTITY_H
#define	ENTITY_H

class Entity {
public:
    Entity();
    virtual ~Entity();

    virtual void update(float dt) = 0;
    virtual void render() const = 0;
private:

};

#endif	/* ENTITY_H */

