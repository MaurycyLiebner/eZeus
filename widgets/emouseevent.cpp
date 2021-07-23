#include "emouseevent.h"

eMouseEvent::eMouseEvent(const int x, const int y,
                         const eMouseButton buttons,
                         const eMouseButton button) :
    mX(x), mY(y), mButtons(buttons), mButton(button) {

}

eMouseEvent eMouseEvent::translated(const int x, const int y) const {
    auto r = *this;
    r.mX += x;
    r.mY += y;
    return r;
}

eMouseEvent eMouseEvent::withPosition(const int x, const int y) const {
    auto r = *this;
    r.mX = x;
    r.mY = y;
    return r;
}
