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
            pnoise.x *= 15.0f;
            pnoise.y *= 15.0f;
            float n = ValueNoise::Eval(pnoise);
            level[i][j] = n;
        }
    }
}

int main(int argc, char* argv[]) {
    // create the window
    srand(time(NULL));
    Gradient::initialize();
    float level[NB_TILES_WIDTH][NB_TILES_HEIGHT];
    sf::Color colors[NB_TILES_WIDTH][NB_TILES_HEIGHT];

    ValueNoise::GenerateValues(rand());
    createMap(level);

    for (unsigned int i = 0; i < NB_TILES_WIDTH; ++i) {
        for (unsigned int j = 0; j < NB_TILES_HEIGHT; ++j) {
            float tileValue = level[i][j];
            colors[i][j] = Gradient::gradient[(int) (tileValue * 255)]; //g.getColor((int) (tileValue * 255));
        }
    }

    sf::Window window(sf::VideoMode(1366, 768), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // run the main loop
    bool running = true;
    while (running) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // end the program
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70, (double) 1366 / 768, 1, 1000);

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // draw...
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(100, 50, 0, 100, 0, 100, 0, 1, 0);

        glPointSize(1.0f);
        glColor3f(0.3f, 0.9f, 0.0f);

        /*glBegin(GL_POINTS);
        for (int i = 0; i < NB_TILES_WIDTH - 1; i++) {
            for (int j = 0; j < NB_TILES_HEIGHT; j++) {

                //Vec3f normal = _terrain->getNormal(x, z);
                //glNormal3f(normal[0], normal[1], normal[2]);
                glColor3f(colors[i][j].r / 255.0f, colors[i][j].g / 255.0f, colors[i][j].b / 255.0f);
                
                if (WATER(level[i][j]))
                {
                    glVertex3f(j, 0.0f, i);
                }
                else
                {
                    glVertex3f(j, (0.35f - level[i][j])*50.0f, i);
                }
                
                //normal = _terrain->getNormal(x, z + 1);
                //glNormal3f(normal[0], normal[1], normal[2]);

            }
        }
         */
for (int j = 0; j < NB_TILES_HEIGHT-1; j++) {
        
            glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < NB_TILES_WIDTH; i++) {

                glColor3f(colors[i][j].r / 255.0f, colors[i][j].g / 255.0f, colors[i][j].b / 255.0f);

                if (WATER(level[i][j])) {
                    glVertex3f(i, 0.0f, j);
                } else {
                    glVertex3f(i, (0.35f - level[i][j])*50.0f, j);
                }

                glColor3f(colors[i][j+1].r / 255.0f, colors[i][j+1].g / 255.0f, colors[i][j+1].b / 255.0f);

                if (WATER(level[i][j+1])) {
                    glVertex3f(i, 0.0f, j+1);
                } else {
                    glVertex3f(i, (0.35f - level[i][j+1])*50.0f, j+1);
                }

            }
            glEnd();
        }


        

        glFlush();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
