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

eMouseWheelEvent::eMouseWheelEvent(const int x, const int y,
                                   const eMouseButton buttons,
                                   const int dy) :
    eMouseEvent(x, y, buttons), mDY(dy) {

}

eMouseWheelEvent eMouseWheelEvent::translated(const int x, const int y) const {
    auto r = *this;
    r.mX += x;
    r.mY += y;
    return r;
}

eMouseWheelEvent eMouseWheelEvent::withPosition(const int x, const int y) const {
    auto r = *this;
    r.mX = x;
    r.mY = y;
    return r;
}
