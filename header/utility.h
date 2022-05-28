#ifndef UTILITY_H_
#define UTILTY_H_

#include "../header/header.h"

bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

void calcSlope(int x1, int y1, int x2, int y2, float *xVal, float *yVal);

#endif