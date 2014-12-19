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

template < typename T>
class VectorView : public sf::Drawable {
public:

    VectorView(const sf::Vector2<T>& vector, const std::string &vectorName = "", const sf::Color &color = sf::Color::Black)
    : m_vector(vector), m_vectorName(vectorName), m_color(color) {
        if (!m_vectorName.empty()) {
            m_textVector = sf::Text(m_vectorName, Font::getFont());
            m_textVector.setOrigin(-4, m_textVector.getCharacterSize());
            m_textVector.setColor(m_color);
        }
    }

    virtual ~VectorView() {
    }

    sf::Vector2<T> getVector() const{
        return m_vector;
    }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {


        // Line
        sf::RectangleShape lineVector(sf::Vector2f(Kinematics::norme(m_vector)*4, 4));
        lineVector.setFillColor(m_color);
        target.draw(lineVector, states);

        // Text
        if (!m_vectorName.empty()) {
            states.transform.translate(lineVector.getPoint(2));
            target.draw(m_textVector, states);
        }
    }


private:
    const sf::Vector2<T>& m_vector;
    std::string m_vectorName;

    // Graphic
    sf::Text m_textVector;
    const sf::Color m_color;
};

#endif	/* VECTORVIEW_H */

