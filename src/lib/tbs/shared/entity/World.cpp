/* 
 * File:   World.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 15:19
 */

#include <SFML/Graphics/Drawable.hpp>

#include "shared/entity/World.h"

World::World() {
}

World::~World() {
}

void World::addEntity(Entity* entity) {
    m_entities.push_back(entity);
}

void World::add(sf::Drawable* entityDrawable) {
    m_entitiesDrawable.push_back(entityDrawable);
}

void World::update(float dt) {
    for (Entity *entity : m_entities) {
        entity->update(dt);
    }
}

void World::render() const {
    for (const sf::Drawable *entity : m_entitiesDrawable) {
//        entity.;
    }
}