#include "ebutton.h"

#include <algorithm>
#include <initializer_list>

#include "esounds.h"

eButton::eButton(eMainWindow* const window) :
    eLabel(window) {}

void eButton::setPressAction(const eAction& a) {
    mPressAction = a;
}

void eButton::setHoverTexture(const std::shared_ptr<eTexture>& tex) {
    mHoverTexture = tex;
}

void eButton::setPressedTexture(const std::shared_ptr<eTexture>& tex) {
    mPressedTexture = tex;
}

void eButton::setDisabledTexture(const std::shared_ptr<eTexture>& tex) {
    mDisabledTexture = tex;
}

int eButton::lineWidth() const {
    return fontSize()/15;
}

void eButton::setEnabled(const bool b) {
    mEnabled = b;
}

bool eButton::enabled() const {
    return mEnabled;
}

void eButton::sizeHint(int& w, int& h) {
    eLabel::sizeHint(w, h);
    w = std::max({w, mTexture ? mTexture->width() : 0,
                  mHoverTexture ? mHoverTexture->width() : 0,
                  mPressedTexture ? mPressedTexture->width() : 0});
    h = std::max({h, mTexture ? mTexture->height() : 0,
                  mHoverTexture ? mHoverTexture->height() : 0,
                  mPressedTexture ? mPressedTexture->height() : 0});
}

void eButton::paintEvent(ePainter& p) {
    if(!mEnabled && mDisabledTexture) {
        p.drawTexture(rect(), mDisabledTexture, eAlignment::center);
    } else if(mPressed && mPressedTexture) {
        p.drawTexture(rect(), mPressedTexture, eAlignment::center);
    } else if(mHover) {
        if(mHoverTexture) {
            p.drawTexture(rect(), mHoverTexture, eAlignment::center);
        } else {
            eLabel::paintEvent(p);
            const auto& t = texture();
            const int tw = t->width();
            const int ww = (width() - tw)/2;
            const int th = t->height();
            const int hh = (height() - th)/2;
            const int ah = height();
            const SDL_Rect brect{ww, ah - hh, width() - 2*ww, lineWidth()};
            p.fillRect(brect, fontColor());
        }
    } else {
        eLabel::paintEvent(p);
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
    eSounds::playButtonSound();
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
