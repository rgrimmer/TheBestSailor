/* 
 * File:   VectorView.h
 * Author: maxence
 *
 * Created on 28 novembre 2014, 13:08
 */

#ifndef VECTORVIEW_H
#define	VECTORVIEW_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "shared/Kinematics.h"
#include "shared/Font.h"

//using namespace std;

class VectorView : public sf::Drawable {
public:

    VectorView(const sf::Vector2f& origin, const sf::Vector2f& vector, const std::string &vectorName = "", const sf::Color &color = sf::Color::Black);
    VectorView(const sf::Vector2f& vector, const std::string &vectorName = "", const sf::Color &color = sf::Color::Black);
    virtual ~VectorView();

    sf::Vector2f getVector() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
    static const sf::Vector2f defaultOrigin;
    const sf::Vector2f& m_origin;
    const sf::Vector2f& m_vector;
    std::string m_vectorName;

    bool originIsLocal = true;

    // Graphic
    sf::Text m_textVector;
    const sf::Color m_color;
};


#endif	/* VECTORVIEW_H */

