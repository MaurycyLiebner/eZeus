#include "etile.h"

#include <random>

eTile::eTile(const int x, const int y) :
    mX(x), mY(y) {
    mAltitude = rand() % 2;
}
