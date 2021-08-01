#include "echeckablebutton.h"

eCheckableButton::eCheckableButton(eMainWindow* const window) :
    eButton(window) {
    setPressAction([this]() {
        mChecked = !mChecked;
    });
}

void eCheckableButton::setCheckAction(const eCheckAction& a) {
    setPressAction([this, a]() {
        mChecked = !mChecked;
        a(mChecked);
    });
}

void eCheckableButton::setChecked(const bool c) {
    mChecked = c;
}

void eCheckableButton::setCheckedTexture(const eTexture& tex) {
    mCheckedTexture = tex;
}

void eCheckableButton::paintEvent(ePainter& p) {
    if(!mCheckedTexture.isNull()) {
        if(mChecked) {
            p.drawTexture(rect(), mCheckedTexture, eAlignment::center);
        } else eButton::paintEvent(p);
    } else {
        if(mChecked) p.drawRect(rect(), {255, 0, 0, 255}, 5);
        else p.drawRect(rect(), {0, 0, 255, 255}, 5);
        eButton::paintEvent(p);
    }
}
