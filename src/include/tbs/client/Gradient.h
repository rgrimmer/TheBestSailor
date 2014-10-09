#pragma once

#define NB_COLORS 9
#define NB_STEPS 255

class Gradient {
public:

    Gradient();
    ~Gradient();

    void CreateGradient();

    static int R[NB_COLORS];
    static int G[NB_COLORS];
    static int B[NB_COLORS];
    static double Percent[NB_COLORS];

    static int GradientR[NB_STEPS];
    static int GradientG[NB_STEPS];
    static int GradientB[NB_STEPS];
};