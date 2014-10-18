#include <SFML/Graphics.hpp>

#include "client/gamestate/GameStateManager.h"
#include "client/ValueNoise.h"
#include "client/TileMap.h"

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

float x = 1.0f;
float posViewX = 0.0f;
float posViewY = 0.0f;
float zoomValue = 1.0f;
bool squared = true;

void generateMap(int width, int height, float* level) {
    float invWidth = 1.f / width, invHeight = 1.f / height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            sf::Vector2f pnoise(j * invWidth, i * invHeight);
            pnoise.x *= 10.0f;
            pnoise.y *= 10.0f;
            float n = ValueNoise::Eval(pnoise);
            level[j + i * width] = n;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    ValueNoise::GenerateSeed();

    /*g_gameStateManager.Initialize();

    while(1) //TODO
    {
            float dt = 0.0f; //TODO
            g_gameStateManager.Update(dt);
    }

    g_gameStateManager.Release();

    return 0;*/

    float level[NB_TILES_WIDTH * NB_TILES_HEIGHT];
    TileMap map;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor"); //, sf::Style::Fullscreen);
    window.setKeyRepeatEnabled(true);

    sf::View currentView = window.getView();
    
    generateMap(NB_TILES_WIDTH, NB_TILES_HEIGHT, level);
    map.load(level, NB_TILES_WIDTH, NB_TILES_HEIGHT, squared);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    ValueNoise::GenerateSeed();
                    generateMap(NB_TILES_WIDTH, NB_TILES_HEIGHT, level);
                    map.load(level, NB_TILES_WIDTH, NB_TILES_HEIGHT, squared);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    posViewX -= 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    posViewX += 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    posViewY -= 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    posViewY += 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    zoomValue += 1.0f;
                    currentView = sf::View(sf::FloatRect(posViewX, posViewY, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    zoomValue -= 1.0f;
                    currentView = sf::View(sf::FloatRect(posViewX, posViewY, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    squared = !squared;
                    map.load(level, NB_TILES_WIDTH, NB_TILES_HEIGHT, squared);
                }

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