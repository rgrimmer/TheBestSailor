/* 
 * File:   BackgroundView.h
 * Author: maxence
 *
 * Created on 31 décembre 2014, 11:29
 */

#ifndef BACKGROUNDVIEW_H
#define	BACKGROUNDVIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>

class BackgroundView : public sf::Drawable {
public:
    static sf::Texture& getTexture();
    
private:
    static bool g_textureIsLoad;
    static sf::Texture g_texture;
    
    
public:
    BackgroundView();
    virtual ~BackgroundView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::View m_backgroundView;
    sf::Sprite m_background;
};

#endif	/* BACKGROUNDVIEW_H */

