#include "echeckablebutton.h"

eCheckableButton::eCheckableButton(eMainWindow* const window) :
    eButton(window) {}

void eCheckableButton::setCheckAction(const eCheckAction& a) {
    setPressAction([this, a]() {
        mChecked = !mChecked;
        a(mChecked);
    });
}

void eCheckableButton::setChecked(const bool c) {
    mChecked = c;
}

void eCheckableButton::paintEvent(ePainter& p) {
    eButton::paintEvent(p);
    if(mChecked) p.drawRect(rect(), {255, 0, 0, 255}, 5);
    else p.drawRect(rect(), {0, 0, 255, 255}, 5);
}
