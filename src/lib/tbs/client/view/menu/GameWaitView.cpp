/* 
 * File:   GameWaitView.cpp
 * Author: maxence
 * 
 * Created on 22 janvier 2015, 13:00
 */

#include "client/view/menu/GameWaitView.h"

GameWaitView::GameWaitView()
: m_timeLeft(-1) {

    // Set center text viewport
    m_centerSfView.setViewport({0.0f, 0.4f, 1.0f, 1.0f});

}

GameWaitView::~GameWaitView() {
}

void GameWaitView::setTimeLeft(float timeLeft) {
    m_timeLeft = timeLeft;
    updateText();
}

void GameWaitView::decreaseTimeLeft(float dt) {
    m_timeLeft -= dt;
    updateText();

}

void GameWaitView::updateText() {
    if (m_timeLeft >= 0) {
        m_leftTimeText = "Game start in " + std::to_string(static_cast<int>(m_timeLeft));
    } else {
        m_leftTimeText = "Please Wait. A game is already start";
    }
}

void GameWaitView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    MenuView::draw(target, states);

    sf::View currentView = target.getView();

    TextView::setAbs(false);

    // Draw InputText
    target.setView(m_centerSfView);
    target.draw(TextView(m_leftTimeText, 60, Center), states);

    target.setView(currentView);
}

