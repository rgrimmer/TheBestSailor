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

#include "client/DetailsView.h"
#include "client/GlobalView.h"

#include "client/network/ClientNetwork.h"

#include "client/state/game/GameStateManager.h"
#include "client/state/game/StateGameStarted.h"

StateGameStarted::StateGameStarted(GameStateManager& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world)
: State()
, m_manager(manager)
, m_network(network)
, m_player(player)
, m_world(world)
, m_followingCamera(true)
, m_zoomValue(1.0f) {
}

StateGameStarted::~StateGameStarted() {

}

void StateGameStarted::initialize(void) {
}

void StateGameStarted::release(void) {
}

void StateGameStarted::activate(void) {
    std::cout << "[GameStarted][Activate]" << std::endl;
    m_globalView = new GlobalView(m_world.getHeightMap(), m_world.getWindMap(), m_world.getClientShip());
    m_detailsView = new DetailsView(m_world);
    m_mainGraphic = dynamic_cast<sf::Drawable*> (m_detailsView);
}

void StateGameStarted::deactivate(void) {
    std::cout << "[GameStarted][Desactivate]" << std::endl;
    m_mainGraphic = nullptr;
    delete m_globalView;
    delete m_detailsView;
}

void StateGameStarted::update(float dt) {
    // @TODO: quit when m_isEnded
    
    sendInfo();

    m_world.update(dt);
}

void StateGameStarted::render(sf::RenderWindow& window) const {

    // Set view position
    if (m_followingCamera) {
        m_detailsView->setCenter(m_world.getClientShip().kinematics().position());
    }

    // Draw view
    if (m_mainGraphic)
        window.draw(*m_mainGraphic);


    // Draw winnner
    /*if (m_endGame != nullptr) {
        window.setView(window.getDefaultView());
        window.draw(TextView(m_winner, 40, TypeAlign::Center));
    }*/
}

void StateGameStarted::sendInfo() const {
    MsgData msg;
    msg << MsgType::Action << static_cast<sf::Uint8> (m_keys.to_ulong()) << sf::Clock;
    m_network.getUdpManager().send(msg);
}

bool StateGameStarted::switchFollowingCamera() {
        m_followingCamera = !m_followingCamera;
        return m_followingCamera;
}

bool StateGameStarted::read(sf::Event& event) {

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
                m_keys.set(TURN_HELM_POSITIVE, true);
                break;
            case sf::Keyboard::Q:
                m_keys.set(TURN_HELM_NEGATIVE, true);
                break;
            case sf::Keyboard::Z:
                m_keys.set(TURN_SAIL_POSITIVE, true);
                break;
            case sf::Keyboard::S:
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
                return false;
                break;
            default:
                break;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::D:
                m_keys.set(TURN_HELM_POSITIVE, false);
                break;
            case sf::Keyboard::Q:
                m_keys.set(TURN_HELM_NEGATIVE, false);
                break;
            case sf::Keyboard::Z:
                m_keys.set(TURN_SAIL_POSITIVE, false);
                break;
            case sf::Keyboard::S:
                m_keys.set(TURN_SAIL_NEGATIVE, false);
                break;
            default:
                break;
        }
    }
    return true;
}

bool StateGameStarted::read(MsgData& msg) {
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

bool StateGameStarted::readGameInfo(MsgData & msg) {
    std::cout << "GameInfo" << std::endl;
    sf::Int32 time;
    msg >> time;
    /*
    if (!MsgData::checkValidity(sf::milliseconds(time), m_lastGameInfo))
        return true;
     * */

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
        ship.kinematics().position() = {positionX, positionY};
        ship.kinematics().speed() = {speedX, speedY};
        std::cout << "Recv ship(" << static_cast<unsigned int> (id) << ") pos(" << positionX << "," << positionY << ") speed(" << speedX << "," << speedY << ")" << std::endl;
    }
    m_world.setClientShip(&m_world.getClientShip());
    return true;
}

bool StateGameStarted::readCheckpoint(MsgData& msg) {
    sf::Uint8 idCheckpoint;

    msg >> idCheckpoint;
    m_world.getCheckPointManager().getCheckPoint(idCheckpoint).activate();
    return true;
}

bool StateGameStarted::readDisconnect(MsgData & msg) {
    sf::Uint8 id;
    msg >> id;
    std::cout << m_world.getShips().erase(static_cast<unsigned int> (id)) << std::endl;
    m_detailsView->updateShips();
    std::cout << "Ship of player " << static_cast<unsigned int> (id) << " remove and view update" << std::endl;
    return true;
}

bool StateGameStarted::readMsgEnd(MsgData & msg) {
    /*msg >> m_winner;
    m_winner.append(" has win");
    m_endGame = new std::thread(&ClientGameSpeedestWin::endScheduler, this);*/
    return true;
}