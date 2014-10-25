/* 
 * File:   World.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 15:19
 */

#ifndef WORLD_H
#define	WORLD_H

#include <vector>

#include "Entity.h"

class World : public Entity {
public:
    World();
    virtual ~World();
    
    void addEntity(Entity* entity);
    void add(sf::Drawable* entityDrawable);
    void update(float dt);
    void render() const;
private:
    
    std::vector<Entity*> m_entities;
    std::vector<sf::Drawable*> m_entitiesDrawable;

};

#endif	/* WORLD_H */

