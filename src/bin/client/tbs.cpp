#include <SFML/Graphics.hpp>

#include "client/gamestate/GameStateManager.h"
#include "client/ValueNoise.h"
#include "client/TileMap.h"
#include "client/PathFinding.h"
#include "client/Gradient.h"

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

float x = 1.0f;
float posViewX = NB_TILES_WIDTH / 2.0f * TILE_SIZE;
float posViewY = NB_TILES_HEIGHT / 2.0f * TILE_SIZE;
float zoomValue = 1.0f;
bool squared = true;

void createMap(float level[NB_TILES_WIDTH][NB_TILES_HEIGHT]) {
    float invWidth = 1.f / NB_TILES_WIDTH, invHeight = 1.f / NB_TILES_HEIGHT;

    for (int i = 0; i < NB_TILES_WIDTH; ++i) {
        for (int j = 0; j < NB_TILES_HEIGHT; ++j) {
            sf::Vector2f pnoise(i * invWidth, j * invHeight);
            pnoise.x *= 20.0f;
            pnoise.y *= 20.0f;
            float n = ValueNoise::Eval(pnoise);
            level[i][j] = n;
        }
    }
}

void drawPath(sf::RenderWindow& w, std::list<position> path, sf::Color c) {
    std::list<position>::iterator z;
    for (z = path.begin(); z != path.end(); z++) {
        sf::RectangleShape rec(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        rec.setFillColor(c);
        rec.setPosition(z->x*TILE_SIZE, z->y * TILE_SIZE);
        w.draw(rec);
    }
}

void findPath(position s, PathFinding::area a, std::list<position> & chemin) {

    int attempts = -1;
    position e;

    do {
        attempts++;

        do {
            e = PathFinding::choosePoint(a);
        } while (s.x == -1);

        if(PathFinding::find(s, e, chemin) == -1 && attempts < 3){
            chemin.clear();
        }
    } while (PathFinding::find(s, e, chemin) == -1 && attempts < 3);
}

void findPaths(std::list<position> & pathNW,
        std::list<position> & pathNE,
        std::list<position> & pathSW,
        std::list<position> & pathSE) {

    position s;

    do {
        s = PathFinding::choosePoint(PathFinding::area_center);
    } while (s.x == -1);

    findPath(s, PathFinding::area_north_west, pathNW);
    findPath(s, PathFinding::area_north_east, pathNE);
    findPath(s, PathFinding::area_south_west, pathSW);
    findPath(s, PathFinding::area_south_east, pathSE);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    Gradient::initialize();


    /*g_gameStateManager.Initialize();

    while(1) //TODO
    {
            float dt = 0.0f; //TODO
            g_gameStateManager.Update(dt);
    }

    g_gameStateManager.Release();

    return 0;*/

    float level[NB_TILES_WIDTH][NB_TILES_HEIGHT];
    TileMap map;
    std::list<position> pathNW;
    std::list<position> pathNE;
    std::list<position> pathSW;
    std::list<position> pathSE;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor"); //, sf::Style::Fullscreen);
    window.setKeyRepeatEnabled(true);

    sf::View currentView = window.getView();

    ValueNoise::GenerateSeed();
    createMap(level);
    PathFinding::initialize(&level);
    findPaths(pathNW, pathNE, pathSW, pathSE);
    map.load(level, squared);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    ValueNoise::GenerateSeed();
                    createMap(level);
                    PathFinding::initialize(&level);
                    findPaths(pathNW, pathNE, pathSW, pathSE);
                    map.load(level, squared);
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
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    squared = !squared;
                    map.load(level, squared);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    PathFinding::initialize(&level);
                    findPaths(pathNW, pathNE, pathSW, pathSE);
                }

            }
        }

        window.clear();
        currentView.setCenter(posViewX, posViewY);
        window.setView(currentView);
        window.draw(map);

        drawPath(window, pathNW, sf::Color(255, 0, 0, 255));
        drawPath(window, pathNE, sf::Color(0, 255, 0, 255));
        drawPath(window, pathSW, sf::Color(255, 255, 0, 255));
        drawPath(window, pathSE, sf::Color(0, 255, 255, 255));

        window.display();
    }

    return 0;
}
