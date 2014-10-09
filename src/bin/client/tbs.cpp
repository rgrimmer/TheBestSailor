#include <SFML/Graphics.hpp>

#include "client/gamestate/GameStateManager.h"
#include "client/ValueNoise.h"
#include "client/TileMap.h"

float x = 1.0f;
float posViewX;
float posViewY;
float zoomValue;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    /*g_gameStateManager.Initialize();

    while(1) //TODO
    {
            float dt = 0.0f; //TODO
            g_gameStateManager.Update(dt);
    }

    g_gameStateManager.Release();

    return 0;*/
    
    unsigned imageWidth = 1360, imageHeight = 768;
    float invImageWidth = 1.f / imageWidth, invImageHeight = 1.f / imageHeight;
    
    ValueNoise simpleNoise2D;

    float   level[imageWidth*imageHeight];
    TileMap map;

    sf::RenderWindow window(sf::VideoMode(imageWidth, imageHeight), "The Best Sailor");
    window.setKeyRepeatEnabled(true);
    
    sf::View currentView = window.getView();
    posViewX = 0.0f;
    posViewY = 0.0f;
    zoomValue = 1.0f;
    
    for (unsigned j = 0; j < imageHeight; ++j) {
        for (unsigned i = 0; i < imageWidth; ++i) {
            sf::Vector2f pnoise(i * invImageWidth, j * invImageHeight);
            pnoise.x *= 10.0f;
            pnoise.y *= 10.0f;
            float n = simpleNoise2D.Eval(pnoise);
            level[i + j * imageWidth] = n;
        }
    }
    
    map.load(sf::Vector2u(200, 200), level, imageWidth, imageHeight);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                posViewX -= 500.0f;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                posViewX += 500.0f;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                posViewY -= 500.0f;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                posViewY += 500.0f;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                zoomValue += 1.0f;
                currentView = sf::View(sf::FloatRect(posViewX,posViewY,imageWidth*zoomValue, imageHeight*zoomValue));
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                zoomValue -= 1.0f;
                currentView = sf::View(sf::FloatRect(posViewX,posViewY,imageWidth*zoomValue, imageHeight*zoomValue));
            }
        }

        window.clear();
        currentView.setCenter(posViewX, posViewY);
        window.setView(currentView);
        window.draw(map);
        window.display();
    }

    return 0;
}