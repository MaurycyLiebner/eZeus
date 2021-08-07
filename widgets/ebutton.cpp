#include "ebutton.h"

#include <algorithm>
#include <initializer_list>

eButton::eButton(eMainWindow* const window) :
    eLabel(window) {}

void eButton::setPressAction(const eAction& a) {
    mPressAction = a;
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
    eLabel::paintEvent(p);
    if(mPressed && !mPressedTexture.isNull()) {
        p.drawTexture(rect(), mPressedTexture, eAlignment::center);
    } else if(mHover) {
        if(!mHoverTexture.isNull()) {
            p.drawTexture(rect(), mHoverTexture, eAlignment::center);
        } else {
            const auto& t = texture();
            const auto tw = t.width();
            const auto ww = (width() - tw)/2;
            const int ah = height();
            const int pd = padding();
            const SDL_Rect brect{ww, ah - pd, width() - 2*ww, 2};
            p.fillRect(brect, {255, 255, 255, 255});
        }
    }
}

bool eButton::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = true;
    return true;
}

bool eButton::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = false;
    if(mPressAction) mPressAction();
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
