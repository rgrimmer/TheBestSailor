/* 
 * File:   ClientStateGameEnd.cpp
 * Author: maxence
 * 
 * Created on 22 janvier 2015, 20:10
 */

#include <iostream>

#include "client/ClientPlayer.h"
#include "client/ClientWorld.h"

#include "client/view/TextView.h"

#include "client/network/ClientNetwork.h"

#include "client/state/game/ClientStateGame.h"
#include "client/state/game/ClientStateGameEnd.h"

ClientStateGameEnd::ClientStateGameEnd(ClientStateGame& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world)
: ClientStateGameStarted(manager, network, player, world) {

}

ClientStateGameEnd::~ClientStateGameEnd() {
}

void ClientStateGameEnd::activate() {
    // Need to reload game
    ClientStateGameStarted::activate();
    std::cout << "[GameEnd][Activate]" << std::endl;
    m_timeLeft.restart();
}

void ClientStateGameEnd::update(float dt) {
    if (m_timeLeft.getElapsedTime() > sf::seconds(5.0f))
        m_manager.reset(); // Return to waitGameState
    ClientStateGameStarted::update(dt);
}

void ClientStateGameEnd::render(sf::RenderWindow& window) const {
    ClientStateGameStarted::render(window);

    window.setView(window.getDefaultView());
    window.draw(TextView("Someone has win the game", 40, TypeAlign::Center));
}

