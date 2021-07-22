#include "emousepressevent.h"

eMouseEvent eMouseEvent::translated(const int x, const int y) const {
    auto r = *this;
    r.mX += x;
    r.mY += y;
    return r;
}
