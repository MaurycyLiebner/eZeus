#include "emovinggameobject.h"

#include <math.h>

void eMovingGameObject::moveToF(const double x, const double y) {
    const int xi = std::floor(x);
    const int yi = std::floor(y);
    moveTo(xi, yi);
    mPosX = x - xi;
    mPosY = y - yi;
}

void eMovingGameObject::moveByF(const double dx, const double dy) {
    mPosX += dx;
    mPosY += dy;
    const int dX = std::floor(mPosX);
    const int dY = std::floor(mPosY);
    moveBy(dX, dY);
    mPosX -= dX;
    mPosY -= dY;
}
