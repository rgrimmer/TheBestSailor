/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"

#include <iostream>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Window/Event.hpp>
#include <cmath>

#include "shared/Utils.h"
#include "client/map/Gradient.h"
#include "client/DisplayInfo.h"
#include "shared/Kinematics.h"

sf::View currentView;
sf::Vector2f posView(2000.0f, 2000.0f);
float zoomValue = 1.0f;
bool squared = true;

/*sf::Packet& operator>>(sf::Packet &packet, MapHeader &header) {
    std::cout << packet.getDataSize() << std::endl;

    //assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);

    sf::Int32 mapWidth;
    sf::Int32 mapHeight;
    sf::Int32 mapSeed;

    packet >> mapWidth >> mapHeight >> mapSeed;


    header = MapHeader(mapWidth, mapHeight, mapSeed);

    std::cout << "packet to map : " << mapWidth << " " << mapHeight << " " << mapSeed << std::endl;

    return packet;
}
 */

sf::Vector2f operator*(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f operator*(const sf::Vector2f &v1, float coef) {
    return sf::Vector2f(v1.x * coef, v1.y * coef);
}

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

#include <iostream>

Client::Client() {
    //            startPollEventThread();
    m_enablePause = true;
    m_timeSpeed = 1.0f;
}

Client::~Client() {
    delete m_detailsView;
    m_socket.disconnect();
}

void Client::start(void) {

    m_ship.kinematics().position() = posView;

    sf::Socket::Status status = m_socket.connect("localhost", SERVER_PORT);
    if (status != sf::Socket::Done) {
        std::cout << "Error connect" << std::endl;
    }

    sf::Packet packet;
    m_socket.send(packet);
    m_socket.receive(packet);

    int width = 600;
    int height = 600;
    int seed = 123456;

    packet >> width >> height >> seed;
    std::cout << width << " " << height << " " << seed << std::endl;

    Gradient::initialize();

    // Data
    m_map = new HeigthMap(MapHeader(height, width, seed));
    m_wind = new WindMap(MapHeader(height, width, seed));

    m_detailsView = new DetailsView(*m_map, *m_wind, m_ship);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");


    window.setKeyRepeatEnabled(true);
    currentView = window.getView();

    m_enableFolowCamera = false;


    //    startAsyncGameLoop(window);

    //    sf::Thread gameLoopThread(std::bind(&Client::gameLoop, this, &window));
    //    gameLoopThread.launch();

    gameLoop(&window);
    //    while (window.isOpen()) {
    //        pollEvent(window);
    //        
    //    }

}

void Client::gameLoop(sf::RenderWindow *window) {
    // Clocks
    sf::Clock clockGlobal;
    sf::Clock clockGameLoop;
    sf::Clock clockFPS;
    int countFram = 0;
    int fps = 0;

    // Display info

    
    DisplayInfo::setWindow(window);

    while (window->isOpen()) {
        window->clear();

        sf::Event event;
        //    std::cout << "start poll" << std::endl;
        //        window.waitEvent(event);
        //        processEvent(window, event);
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        posView.x -= 500.0f;
                        break;
                    case sf::Keyboard::Right:
                        posView.x += 500.0f;
                        break;
                    case sf::Keyboard::Up:
                        posView.y -= 500.0f;
                        break;
                    case sf::Keyboard::Down:
                        posView.y += 500.0f;
                        break;
                    case sf::Keyboard::Add:
                        zoomValue *= 2.0f;
                        currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                        break;
                    case sf::Keyboard::Subtract:
                        zoomValue /= 2.0f;
                        currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                        break;
                    case sf::Keyboard::Q:
                        m_ship.helm().turn(5.0f);
                        break;
                    case sf::Keyboard::D:
                        m_ship.helm().turn(-5.0f);
                        break;
                    case sf::Keyboard::Z:
                        m_ship.sail().setAngle(m_ship.sail().getAngle() + 5.0f);
                        break;
                    case sf::Keyboard::S:
                        m_ship.sail().setAngle(m_ship.sail().getAngle() - 5.0f);
                        break;
                    case sf::Keyboard::A:
                        m_detailsView->switchSquared();
                        break;
                    case sf::Keyboard::W:
                        m_detailsView->switchEnableWind();
                        break;
                    case sf::Keyboard::C:
                        m_enableFolowCamera = !m_enableFolowCamera;
                        break;
                    case sf::Keyboard::P:
                        m_enablePause = !m_enablePause;
                        break;
                    case sf::Keyboard::I:
                        m_timeSpeed /= 2.0f;
                        break;
                    case sf::Keyboard::O:
                        m_timeSpeed *= 2.0f;
                        break;
                    default:
                        break;
                }
            }
        }



        // Update
        float timeLoop = clockGameLoop.getElapsedTime().asSeconds();
        clockGameLoop.restart();

        // Update ship

        Wind wind = m_wind->wind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

        sf::Vector2f shipVector = m_ship.kinematics().speed();
        sf::Vector2f windVector = wind.getVector();

        sf::Vector2f coefSail(1.0f, 1.0f);
        sf::Vector2f coefHelm(1.0f, 1.0f);
        
        sf::Vector2f frottement(0.001f, 0.001f);
        sf::Vector2f apparentWind = windVector - shipVector;
        
        float apparentWindDir = Kinematics::direction(apparentWind);
        float sailDir = Kinematics::degToRad(m_ship.sail().getAngle());
        float helmDir = Kinematics::degToRad(m_ship.helm().angle());
        float shipDir = Kinematics::degToRad(Kinematics::direction(m_ship.kinematics().speed()));
        if(isnan(shipDir))
            shipDir = 0;
        
        float angleAlpha = 0.0f;    // @TODO angle ventApparent - voile
//        float angleAlpha = 
        float angleBeta = shipDir - sailDir;     // @TODO angle axe du bateau - voile 
        
        // Equation from https://www.ensta-bretagne.fr/jaulin/jaulincifa2004.pdf
        
        sf::Vector2f sailVector = 
                coefSail * (
                windVector * std::cos(shipDir + angleBeta) 
                - shipVector * std::sin(shipDir)
                );
        
        sf::Vector2f helmVector = coefHelm * shipVector * std::sin(helmDir);
        
        sf::Vector2f forceDePousser1 = 
                (sailVector * std::sin(angleBeta)
                - helmVector * std::sin(helmDir)
                - shipVector * frottement)
                / 1.0f; // Masse
        
        // Equation from wikipedia
        sf::Vector2f CONSTANTE(0.1f, 0.1f);
        float sinAB = std::sin(angleAlpha + angleBeta);
        sf::Vector2f forceDePousser2 = CONSTANTE * sinAB * angleAlpha - helmVector * std::sin(helmDir);
        
        sf::Vector2f forceDePousser = forceDePousser1;
        
        m_ship.kinematics().acceleration() = forceDePousser /* Kinematics::vectorDir(degToRad(angleDirShip))*/;
        
        
        if(!m_enablePause) {
            m_ship.update(timeLoop*m_timeSpeed);
        }

        // Draw
        
        // Set view position
        if (m_enableFolowCamera) {
            currentView.setCenter(m_ship.kinematics().position());
        } else {
            currentView.setCenter(posView);
        }
        window->setView(currentView);
        
        // Draw view
        window->draw(*m_detailsView);

        // Draw vent apparent
        VectorView<float> ventAppView(apparentWind, "Va", sf::Color::Green);
        sf::Transform tApp;
        tApp.translate(m_ship.kinematics().position());
        window->draw(ventAppView, tApp);


        // Display information : 
        DisplayInfo::setZoom(zoomValue);
        DisplayInfo::setTopLeftPosition(posView - sf::Vector2f(SCREEN_WIDTH / 2 * zoomValue, SCREEN_HEIGHT / 2 * zoomValue));

        // Clocks infos
        DisplayInfo::draw(std::to_string(clockGlobal.getElapsedTime().asSeconds()));
        DisplayInfo::draw("fps : " + std::to_string(fps));

        // Data infos
        DisplayInfo::draw("ship :");
        DisplayInfo::draw("ship :" + std::to_string(shipDir));
        DisplayInfo::draw("acc : " + std::to_string(m_ship.kinematics().acceleration().x) + " " + std::to_string(m_ship.kinematics().acceleration().y));
        DisplayInfo::draw("speed : " + std::to_string(m_ship.kinematics().speed().x) + " " + std::to_string(m_ship.kinematics().speed().y));
        DisplayInfo::draw("pos : " + std::to_string(m_ship.kinematics().position().x) + " " + std::to_string(m_ship.kinematics().position().y));
//        DisplayInfo::draw("dir : " + std::to_string(dir.x) + " " + std::to_string(dir.y) + ". norme : " + std::to_string(Kinematics::norme(m_ship.kinematics().speed())));

        //DisplayInfo::draw("wind : " + m_windView.force(m_ship.getPosition()).toString());

        // Draw infos
        DisplayInfo::draw("Wind Direction/Force: " + std::to_string(wind.direction()) + " " + std::to_string(wind.force()));
        DisplayInfo::draw("WindVector: " + std::to_string(windVector.x) + " " + std::to_string(windVector.y));
        DisplayInfo::draw("VentApparent : " + std::to_string(apparentWind.x) + " " + std::to_string(apparentWind.y));
        DisplayInfo::draw("sailVector : " + std::to_string(sailVector.x) + " " + std::to_string(sailVector.y));
        DisplayInfo::draw("helmVector : " + std::to_string(helmVector.x) + " " + std::to_string(helmVector.y));
        DisplayInfo::draw("ForceDePousser : " + std::to_string(forceDePousser.x) + " " + std::to_string(forceDePousser.y));


        if (clockFPS.getElapsedTime().asSeconds() >= 1) {
            fps = countFram;
            countFram = 0;
            clockFPS.restart();
        } else {
            ++countFram;
        }
        window->display();

    }

    m_socket.disconnect();
}