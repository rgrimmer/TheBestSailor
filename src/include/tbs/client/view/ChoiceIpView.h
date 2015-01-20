/* 
 * File:   ChoiceIpView.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 20:08
 */

#ifndef CHOICEIPVIEW_H
#define	CHOICEIPVIEW_H

#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "client/view/BackgroundView.h"
#include "TextView.h"

class ChoiceIpView : public sf::Drawable {
public:
    ChoiceIpView(const std::string& ipAddressText);
    virtual ~ChoiceIpView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    BackgroundView m_backgroundView;

    sf::View m_titleView;
    TextView m_titleSfText;

    sf::View m_ipEnterSfView;
    const std::string& m_ipAddressText;
    
    sf::View m_ipInfoSfView;
    TextView m_fixedTextView1;
    TextView m_fixedTextView2;
    TextView m_fixedTextView3;
};

#endif	/* CHOICEIPVIEW_H */

