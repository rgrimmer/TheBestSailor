#pragma once

#include <SFML/Graphics.hpp>

#define MAX_VERTICES 256

class ValueNoise {
public:
    ValueNoise();
    ~ValueNoise();

    float Eval(const sf::Vector2f &pt);

private:
    float Smoothstep(const float & t);
    float Mix(const float &a, const float &b, const float &t);

public:


private:
    static const unsigned int maxVerticesMask = MAX_VERTICES - 1;
    float r[ MAX_VERTICES * MAX_VERTICES ];

};