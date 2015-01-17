/* 
 * File:   GameStateWaitGame.cpp
 * Author: maxence
 * 
 * Created on 16 janvier 2015, 23:28
 */
#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgAction.h"

#include "client/gamestate/GameStateGame.h"

GameStateGame::GameStateGame(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player)
: GameState(window, network, player)
, m_world()
, m_hasInfoToSend(false)
, m_isEnded(false)
, m_enableFolowCamera(true)
, m_countFrames(0)
, m_lastCoutFrames(0)
, m_keys()
, m_mainGraphic(nullptr)
, m_detailsView(nullptr)
, m_globalView(nullptr)
, m_currentView(m_window.getView())
, m_music() {

}

GameStateGame::~GameStateGame() {
}

void GameStateGame::Activate() {
    std::cout << "[Client][Game][Init]" << std::endl;

    m_globalView = new GlobalView(m_world.getHeightMap(), m_world.getWindMap(), m_world.getClientShip());
    m_detailsView = new DetailsView(m_world);
    m_mainGraphic = dynamic_cast<sf::Drawable*> (m_detailsView);
    m_enableFolowCamera = true;
    m_window.setKeyRepeatEnabled(false);
    /*if (m_music.openFromFile("./share/tbs/sound/music_414.mp3")) {
        m_music.setLoop(true);
        m_music.play();
    }*/

    std::cout << "[Client][Game][Start]" << std::endl;
}

void GameStateGame::DeActivate() {
    m_mainGraphic = nullptr;
    m_music.stop();
    delete m_globalView;
    delete m_detailsView;
}

void GameStateGame::Initialize() {

}

void GameStateGame::Release() {

}

void GameStateGame::Update(float dt) {

    //TODO: quit when m_isEnded
    MsgData msg;
    msg << MsgType::Action << static_cast<sf::Uint8> (m_keys.to_ulong()) << dt;
    m_network.getUdpManager().send(msg);
    
    //m_world.update(dt);
}

void GameStateGame::Render(sf::RenderWindow& window) {

    if (&(m_world.getClientShip()) == nullptr)
        return;

    // Set view position
    if (m_enableFolowCamera) {
        m_currentView.setCenter(m_world.getClientShip().kinematics().position());
    }

    m_window.setView(m_currentView);

    // Draw view
    if (m_mainGraphic)
        m_window.draw(*m_mainGraphic);

    // Draw winnner
    /*if (m_endGame != nullptr) {
        m_window.setView(m_window.getDefaultView());
        m_window.draw(TextView(m_winner, 40, TypeAlign::Center));
    }*/
    /*
    TextView::setAbs(true);
    TextView::update();
     */
    m_window.display();
}

bool GameStateGame::read(sf::Event& event) {
    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        return false;
    }
    return true;
}

bool GameStateGame::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    std::cout << "type : " << (int)msgType << std::endl;
    switch (msgType) {
        case MsgType::Game:
            return readInitGame(msg);
        case MsgType::GameInfo:
            return readGameInfo(msg);
        case MsgType::Disconnect:
            return readDisconnect(msg);
        case MsgType::Checkpoint:
            return readCheckpoint(msg);
        case MsgType::GameEnd:
            return readMsgEnd(msg);
        default:
            return false;
    }
    
    return true;
}

bool GameStateGame::readInitGame(MsgData & msg) {
    sf::Int32 width, height, seedHeight, seedWind;
    sf::Int32 checkPointCount;
    sf::Int32 shipCount;
    msg >> height >> width >> seedHeight >> seedWind;
    
    m_world.initialize();
    std::cout << "RECEIVE map(" << height << ", " << width << ", " << seedHeight << ", " << seedWind << ")" << std::endl;
    m_world.initializeMap(width, height, seedHeight, seedWind);
    
    msg >> checkPointCount;
    for (int i = 0; i < checkPointCount; ++i) {
        sf::Vector2i posCheckPoint;
        msg >> posCheckPoint.x >> posCheckPoint.y;
        
        m_world.addCheckPoint(posCheckPoint);
    }
    
    msg >> shipCount;
    
    for(int i = 0; i < shipCount; ++i) {
        sf::Uint8 id;
        msg >> id;
        Ship& ship = m_world.getShips()[static_cast<unsigned int>(id)];
        auto& shipPos = ship.kinematics().position();
        msg >> shipPos.x >> shipPos.y;
        ship.setAngle(90.0f);
        ship.getSail().setAngle(m_world.getWindMap().wind(static_cast<sf::Vector2i>(shipPos)).getDirection());
    }
    
    return true;
}

bool GameStateGame::readGameInfo(MsgData & msg) {
    std::cout << "GameInfo" << std::endl;
    sf::Int32 time;
    msg >> time;
    if (!MsgData::checkValidity(sf::milliseconds(time), m_lastGameInfo))
        return false;

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
    m_world.setClientShip(&m_world.getShips()[m_player.getId()]);
    return true;
}

bool GameStateGame::readDisconnect(MsgData & msg) {
    sf::Uint8 id;
    msg >> id;
    std::cout << m_world.getShips().erase(static_cast<unsigned int> (id)) << std::endl;
    m_detailsView->updateShips();
    std::cout << "Ship of player " << static_cast<unsigned int> (id) << " remove and view update" << std::endl;
    return true;
}

bool GameStateGame::readCheckpoint(MsgData& msg) {
    sf::Uint8 idCheckpoint;
    
    msg >> idCheckpoint;
    
    m_world.getCheckPointManager().getCheckPoint(idCheckpoint).activate();
    return true;
}

bool GameStateGame::readMsgEnd(MsgData& msg) {
    /*msg >> m_winner;
    m_winner.append(" has win");
    m_endGame = new std::thread(&ClientGameSpeedestWin::endScheduler, this);*/
    return true;
}