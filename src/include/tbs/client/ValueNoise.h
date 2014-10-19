#pragma once

#include <SFML/Graphics.hpp>

#define MAX_VERTICES 256

class ValueNoise {
public:
    static void  GenerateValues(int seed);
    static float Eval(const sf::Vector2f &pt);

private:
    static float Smoothstep(const float & t);
    static float Mix(const float &a, const float &b, const float &t);

public:

    static const int maxVerticesMask;
    static float r[ MAX_VERTICES * MAX_VERTICES ];

};