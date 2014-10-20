#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "client/gamestate/GameStateManager.h"
#include "client/ValueNoise.h"
#include "client/TileMap.h"
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

int main(int argc, char* argv[]) {
   // create the window
    
    Gradient::initialize();
    
    
    
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        glBegin(GL_TRIANGLES);
            glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
            glColor3ub(0,255,0);    glVertex2d(0,0.75);
            glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
        glEnd();

        glFlush();
        
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
