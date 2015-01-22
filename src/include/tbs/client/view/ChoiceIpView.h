/* 
 * File:   ChoiceIpView.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 20:08
 */

#ifndef CHOICEIPVIEW_H
#define	CHOICEIPVIEW_H

#include <string>

#include "client/view/TextView.h"
#include "client/view/menu/MenuView.h"

class ChoiceIpView : public MenuView {
public:
    ChoiceIpView(const std::string& ipAddressText);
    virtual ~ChoiceIpView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::View m_ipEnterSfView;
    const std::string& m_ipAddressText;
    
    sf::View m_ipInfoSfView;
    TextView m_fixedTextView1;
    TextView m_fixedTextView2;
    TextView m_fixedTextView3;
};

#endif	/* CHOICEIPVIEW_H */

