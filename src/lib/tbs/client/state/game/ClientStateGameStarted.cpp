/* 
 * File:   StateGameStarted.cpp
 * Author: maxence
 * 
 * Created on 16 janvier 2015, 23:28
 */
#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"
#include "shared/network/MsgAction.h"

#include "client/ClientPlayer.h"
#include "client/ClientWorld.h"

#include "client/view/DetailsView.h"
#include "client/view/GlobalView.h"

#include "client/network/ClientNetwork.h"

#include "client/state/ClientState.h"
#include "client/state/game/ClientStateGame.h"
#include "client/state/game/ClientStateGameStarted.h"
#include "client/network/Input.h"

ClientStateGameStarted::ClientStateGameStarted(ClientStateGame& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world)
: State()
, m_manager(manager)
, m_network(network)
, m_player(player)
, m_world(world)
, m_followingCamera(true)
, m_zoomValue(1.0f) {
}

ClientStateGameStarted::~ClientStateGameStarted() {

}

void ClientStateGameStarted::release(void) {
}

void ClientStateGameStarted::activate(void) {
    std::cout << "[GameStarted][Activate]" << std::endl;
    m_globalView = new GlobalView(m_world.getHeightMap(), m_world.getWindMap(), m_world.getClientShip());
    m_detailsView = new DetailsView(m_world);
    m_mainGraphic = dynamic_cast<sf::Drawable*> (m_detailsView);
}

void ClientStateGameStarted::deactivate(void) {
    std::cout << "[GameStarted][Desactivate]" << std::endl;
    m_mainGraphic = nullptr;
    delete m_globalView;
    delete m_detailsView;
}

void ClientStateGameStarted::update(float dt) {
    Input input(m_keys, m_clock.getElapsedTime());
    
//    m_world.update(dt);
    sf::Uint32 id = m_predictions.add(input);
    sendInfo(input, id);
}

void ClientStateGameStarted::render(sf::RenderWindow& window) const {

    // Set view position
    if (m_followingCamera) {
        m_detailsView->setCenter(m_world.getClientShip().getPosition());
    }

    // Draw view
    if (m_mainGraphic)
        window.draw(*m_mainGraphic);


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        TextView::setAbs(true);
        window.draw(TextView("D", 200, TypeAlign::Center));
    }
    // Draw winnner
    /*if (m_endGame != nullptr) {
        window.setView(window.getDefaultView());
        window.draw(TextView(m_winner, 40, TypeAlign::Center));
    }*/
}

void ClientStateGameStarted::sendInfo(const Input &input, sf::Uint32 id) {
    MsgData msg;
    msg << MsgType::Action << static_cast<sf::Uint8> (input.getActions().to_ulong()) << id;
    m_network.getUdpManager().send(msg);
}

bool ClientStateGameStarted::switchFollowingCamera() {
    m_followingCamera = !m_followingCamera;
    return m_followingCamera;
}

bool ClientStateGameStarted::read(sf::Event& event) {

    if (event.type == sf::Event::Closed) {
        return false;
    } else if (event.type == sf::Event::Resized) {
        m_detailsView->getView().setSize({event.size.width * m_zoomValue, event.size.height * m_zoomValue});
    } else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                m_detailsView->getView().move(-5.0f * m_zoomValue, 0.0f);
                break;
            case sf::Keyboard::Right:
                m_detailsView->getView().move(5.0f * m_zoomValue, 0.0f);
                break;
            case sf::Keyboard::Up:
                m_detailsView->getView().move(0.0f, -5.0f * m_zoomValue);
                break;
            case sf::Keyboard::Down:
                m_detailsView->getView().move(0.0f, 5.0f * m_zoomValue);
                break;

            case sf::Keyboard::L:
            case sf::Keyboard::Subtract:
                m_zoomValue *= 2.0f;
                m_detailsView->getView().zoom(2.0f);
                break;

            case sf::Keyboard::P:
            case sf::Keyboard::Add:
                m_zoomValue *= 0.5f;
                m_detailsView->getView().zoom(0.5f);
                break;
            case sf::Keyboard::D:
                m_world.getClientShip().setTurningPositive(true);
                m_keys.set(TURN_HELM_POSITIVE, true);
                break;
            case sf::Keyboard::Q:
                m_world.getClientShip().setTurningNegative(true);
                m_keys.set(TURN_HELM_NEGATIVE, true);
                break;
            case sf::Keyboard::Z:
                m_world.getClientShip().getSail().setTurningPositive(true);
                m_keys.set(TURN_SAIL_POSITIVE, true);
                break;
            case sf::Keyboard::S:
                m_world.getClientShip().getSail().setTurningNegative(true);
                m_keys.set(TURN_SAIL_NEGATIVE, true);
                break;
            case sf::Keyboard::A:
                m_detailsView->switchSquared();
                break;
            case sf::Keyboard::W:
                m_detailsView->switchEnableWind();
                break;
            case sf::Keyboard::C:
                switchFollowingCamera();
                break;
            case sf::Keyboard::M:
                m_mainGraphic = (m_mainGraphic == dynamic_cast<sf::Drawable*> (m_detailsView)) ? dynamic_cast<sf::Drawable*> (m_globalView) : dynamic_cast<sf::Drawable*> (m_detailsView);
                break;
            case sf::Keyboard::Escape:
                m_manager.getManager().pop();
                break;
            default:
                break;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::D:
                m_keys.set(TURN_HELM_POSITIVE, false);
                m_world.getClientShip().setTurningPositive(false);
                break;
            case sf::Keyboard::Q:
                m_keys.set(TURN_HELM_NEGATIVE, false);
                m_world.getClientShip().setTurningNegative(false);
                break;
            case sf::Keyboard::Z:
                m_keys.set(TURN_SAIL_POSITIVE, false);
                m_world.getClientShip().getSail().setTurningPositive(false);
                break;
            case sf::Keyboard::S:
                m_keys.set(TURN_SAIL_NEGATIVE, false);
                m_world.getClientShip().getSail().setTurningNegative(false);
                break;
            default:
                break;
        }
    }
    return true;
}

bool ClientStateGameStarted::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::GameInfo:
            return readGameInfo(msg);
        case MsgType::Disconnect:
            return readDisconnect(msg);
        case MsgType::Checkpoint:
            return readCheckpoint(msg);
        case MsgType::GameEnd:
            return readMsgEnd(msg);
        default:
            return true;
    }
}

bool ClientStateGameStarted::readGameInfo(MsgData & msg) {
    std::cout << "GameInfo" << std::endl;
    sf::Uint32 idReq;
    msg >> idReq;

    while (!msg.endOfPacket()) {

        sf::Uint8 id;
        float shipAngle;
        float sailAngle;
        float positionX;
        float positionY;
        float speedX;
        float speedY;

        msg >> id >> shipAngle >> sailAngle >> positionX >> positionY >> speedX >> speedY;

        Ship &ship = m_world.getShips()[static_cast<unsigned int> (id)];
        ship.setAngle(shipAngle);
        ship.getSail().setAngle(sailAngle);
        ship.position() = {positionX, positionY};
        ship.velocity() = {speedX, speedY};
        std::cout << "Recv ship(" << static_cast<unsigned int> (id) << ") pos(" << positionX << "," << positionY << ") speed(" << speedX << "," << speedY << ")" << std::endl;
    }

//    updatePrediction(idReq);
    return true;
}

void ClientStateGameStarted::updatePrediction(sf::Uint32 reqId) {
    std::vector<Input> predictions = m_predictions.getInputFrom(reqId);
    std::cout << "nbPrediction(" << predictions.size() << ")" << std::endl;
    Input* prevInput = &predictions[0];
 
    sf::Vector2f oldShipPos = m_world.getClientShip().getPosition();
    
    for (unsigned int i = 1; i < predictions.size(); ++i) {

        // Set state of world 
        Ship& ship = m_world.getClientShip();
        ship.setTurningNegative(prevInput->getActions().test(TURN_HELM_NEGATIVE));
        ship.setTurningPositive(prevInput->getActions().test(TURN_HELM_POSITIVE));
        ship.getSail().setTurningNegative(prevInput->getActions().test(TURN_SAIL_NEGATIVE));
        ship.getSail().setTurningPositive(prevInput->getActions().test(TURN_SAIL_POSITIVE));

        // Update
        sf::Time diffTime = predictions[i].getTime() - prevInput->getTime();
        m_world.updateShip(m_world.getClientShip(), diffTime.asSeconds());

        // Go to the next predictions
        prevInput = &predictions[i];
    }
    
    // Set state of world 
    Ship& ship = m_world.getClientShip();
    sf::Vector2f& newShipPos = ship.position();
    
    // Smooth correction
//    sf::Vector2f diffPos = newShipPos - oldShipPos;
//    if(std::abs(diffPos.x) < 1) {
//        newShipPos.x =  oldShipPos.x + (diffPos.x * 0.2);
//    }
//    if(std::abs(diffPos.y) < 1) {
//        newShipPos.y =  oldShipPos.y + (diffPos.y * 0.2);
//    }
    
    ship.setTurningNegative(prevInput->getActions().test(TURN_HELM_NEGATIVE));
    ship.setTurningPositive(prevInput->getActions().test(TURN_HELM_POSITIVE));
    ship.getSail().setTurningNegative(prevInput->getActions().test(TURN_SAIL_NEGATIVE));
    ship.getSail().setTurningPositive(prevInput->getActions().test(TURN_SAIL_POSITIVE));

}

bool ClientStateGameStarted::readCheckpoint(MsgData& msg) {
    sf::Uint8 idCheckpoint;

    msg >> idCheckpoint;
    m_world.getCheckPointManager().getCheckPoint(idCheckpoint).activate();
    return true;
}

bool ClientStateGameStarted::readDisconnect(MsgData & msg) {
    sf::Uint8 id;
    msg >> id;
    m_world.getShips().erase(static_cast<unsigned int> (id));
    m_detailsView->updateShips();
    std::cout << "Ship of player " << static_cast<unsigned int> (id) << " remove and view update" << std::endl;
    return true;
}

bool ClientStateGameStarted::readMsgEnd(MsgData & msg) {
    m_manager.push(EStateGame::End);
    return true;
}