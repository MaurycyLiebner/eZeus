#include "ebutton.h"

#include <algorithm>
#include <initializer_list>

eButton::eButton(eMainWindow* const window) :
    eLabel(window) {}

void eButton::setPressAction(const eAction& a) {
    mPressAction = a;
}

void eButton::setTexture(const eTexture& tex) {
    mTexture = tex;
}

void eButton::setHoverTexture(const eTexture& tex) {
    mHoverTexture = tex;
}

void eButton::setPressedTexture(const eTexture& tex) {
    mPressedTexture = tex;
}

void eButton::sizeHint(int& w, int& h) {
    eLabel::sizeHint(w, h);
    w = std::max({w, mTexture.width(),
                  mHoverTexture.width(),
                  mPressedTexture.width()});
    h = std::max({h, mTexture.height(),
                  mHoverTexture.height(),
                  mPressedTexture.height()});
}

void eButton::paintEvent(ePainter& p) {
    p.drawRect(rect(), {0, 0, 0, 255}, 5);
    if(mPressed && !mPressedTexture.isNull()) {
        p.drawTexture(rect(), mPressedTexture, eAlignment::center);
    } else if(mHover && !mHoverTexture.isNull()) {
        p.drawTexture(rect(), mHoverTexture, eAlignment::center);
    } else if(!mTexture.isNull()) {
        p.drawTexture(rect(), mTexture, eAlignment::center);
    }
    eLabel::paintEvent(p);
}

bool eButton::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = true;
    if(mPressAction) mPressAction();
    return true;
}

bool eButton::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = false;
    return true;
}

bool eButton::mouseMoveEvent(const eMouseEvent& e) {
    (void)e;
    return true;
}

bool eButton::mouseEnterEvent(const eMouseEvent& e) {
    (void)e;
    mHover = true;
    return true;
}

bool eButton::mouseLeaveEvent(const eMouseEvent& e) {
    (void)e;
    mHover = false;
    return true;
}
