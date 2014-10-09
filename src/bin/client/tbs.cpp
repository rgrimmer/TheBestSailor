#include <SFML/Graphics.hpp>

#include "client/gamestate/GameStateManager.h"
#include "client/ValueNoise.h"
#include "client/Gradient.h"

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

    ValueNoise simpleNoise2D;
    Gradient g;
    g.CreateGradient();

    unsigned imageWidth = 800, imageHeight = 600;
    float invImageWidth = 1.f / imageWidth, imvImageHeight = 1.f / imageHeight;


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (unsigned j = 0; j < imageHeight; ++j) {
            for (unsigned i = 0; i < imageWidth; ++i) {
                sf::Vector2f pnoise(i * invImageWidth, j * imvImageHeight);
                pnoise.x *= 10.0f;
                pnoise.y *= 10.0f;
                float n = simpleNoise2D.Eval(pnoise);

                sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                sf::Color c(g.GradientR[(int) (n * 255)], g.GradientG[(int) (n * 255)], g.GradientB[(int) (n * 255)], 255);

                rectangle.setPosition(i, j);
                rectangle.setFillColor(c);

                window.draw(rectangle);
            }
        }

        window.display();
    }

    return 0;
}