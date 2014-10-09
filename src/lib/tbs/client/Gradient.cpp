#include "client/Gradient.h"
#include <cstdio>

int Gradient::R[NB_COLORS] = {255, 179, 153, 115, 42, 69, 17, 9, 2};
int Gradient::G[NB_COLORS] = {255, 179, 143, 128, 102, 108, 82, 62, 43};
int Gradient::B[NB_COLORS] = {255, 179, 92, 77, 41, 118, 112, 92, 68};
double Gradient::Percent[NB_COLORS] = {0.0, 5.0, 15.0, 25.0, 49.9, 50.0, 51.0, 75.0, 100.0};

int Gradient::GradientR[NB_STEPS];
int Gradient::GradientG[NB_STEPS];
int Gradient::GradientB[NB_STEPS];

Gradient::Gradient() {

}

Gradient::~Gradient() {

}

void Gradient::CreateGradient() {
    int counter = 0;
    int pos1, pos2, pDiff;
    int rDiff, gDiff, bDiff;
    float rStep, gStep, bStep;

    while (counter < NB_COLORS - 1) {
        pos1 = Percent[counter] * NB_STEPS / 100;
        pos2 = Percent[counter + 1] * NB_STEPS / 100;

        pDiff = pos2 - pos1;

        rDiff = R[counter] - R[counter + 1];
        gDiff = G[counter] - G[counter + 1];
        bDiff = B[counter] - B[counter + 1];

        rStep = rDiff * 1.0 / pDiff;
        gStep = gDiff * 1.0 / pDiff;
        bStep = bDiff * 1.0 / pDiff;

        for (int i = 0; i < pDiff; ++i) {
            GradientR[pos1 + i] = (int) (R[counter] - (rStep * i));
            GradientG[pos1 + i] = (int) (G[counter] - (gStep * i));
            GradientB[pos1 + i] = (int) (B[counter] - (bStep * i));
        }

        counter++;
    }
}