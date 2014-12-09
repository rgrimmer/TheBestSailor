/* 
 * File:   EntityView.h
 * Author: maxence
 *
 * Created on 7 décembre 2014, 18:48
 */

#ifndef ENTITYVIEW_H
#define	ENTITYVIEW_H

#include <SFML/Graphics/Drawable.hpp>

template<typename T> class EntityView; 

template<typename T> 
class EntityView : public sf::Drawable {
public:
    template<typename T> 
    EntityView(const T &model) : m_model(model) {};
    virtual ~EntityView() = 0;
    
    template<typename T> 
    inline const T &model() const { return m_model; }
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    const T &m_model;

};

#endif	/* ENTITYVIEW_H */

