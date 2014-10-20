#pragma once

#define NB_COLORS 9
#define NB_STEPS 255

class Gradient {
public:

    static void initialize();

    static int R[NB_COLORS];
    static int G[NB_COLORS];
    static int B[NB_COLORS];
    static double Percent[NB_COLORS];
    static sf::Color gradient[NB_STEPS];
};