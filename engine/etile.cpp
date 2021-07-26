#include "etile.h"

#include <random>

int gId = 0;

eTile::eTile(const int x, const int y) :
    mId(gId++), mX(x), mY(y) {}
