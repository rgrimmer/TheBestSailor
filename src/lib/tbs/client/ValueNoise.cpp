#include <cmath>
#include <stdlib.h>

#include "client/ValueNoise.h"

float ValueNoise::r[ MAX_VERTICES * MAX_VERTICES ];
const int ValueNoise::maxVerticesMask = MAX_VERTICES - 1;

void ValueNoise::GenerateSeed() {
    for (unsigned i = 0; i < MAX_VERTICES * MAX_VERTICES; ++i) {
        r[ i ] = rand() % 100 / 100.0f;
    }
}

float ValueNoise::Eval(const sf::Vector2f &pt) {
    int xi = floor(pt.x);
    int yi = floor(pt.y);

    float tx = pt.x - xi;
    float ty = pt.y - yi;

    int rx0 = xi & maxVerticesMask;
    int rx1 = (rx0 + 1) & maxVerticesMask;
    int ry0 = yi & maxVerticesMask;
    int ry1 = (ry0 + 1) & maxVerticesMask;

    /// Random values at the corners of the cell
    const float & c00 = r[ ry0 * maxVerticesMask + rx0 ];
    const float & c10 = r[ ry0 * maxVerticesMask + rx1 ];
    const float & c01 = r[ ry1 * maxVerticesMask + rx0 ];
    const float & c11 = r[ ry1 * maxVerticesMask + rx1 ];

    /// Remapping of tx and ty using the Smoothstep function
    float sx = Smoothstep(tx);
    float sy = Smoothstep(ty);

    /// Linearly interpolate values along the x axis
    float nx0 = Mix(c00, c10, sx);
    float nx1 = Mix(c01, c11, sx);

    /// Linearly interpolate the nx0/nx1 along they y axis
    return Mix(nx0, nx1, sy);
}

float ValueNoise::Smoothstep(const float & t) {
    return t * t * (3 - 2 * t);
}

float ValueNoise::Mix(const float &a, const float &b, const float &t) {
    return a * (1 - t) + b * t;
}
