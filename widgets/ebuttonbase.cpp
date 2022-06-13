#include "ebuttonbase.h"

#include "esounds.h"

void eButtonBase::setPressAction(const eAction& a) {
    mPressAction = a;
}

int eButtonBase::lineWidth() const {
    return std::max(1, fontSize()/15);
}

void eButtonBase::setEnabled(const bool b) {
    mEnabled = b;
}

bool eButtonBase::enabled() const {
    return mEnabled;
}

bool eButtonBase::pressed() const {
    return mPressed;
}

bool eButtonBase::hovered() const {
    return mHover;
}

bool eButtonBase::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = true;
    return true;
}

bool eButtonBase::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    mPressed = false;
    if(mPressAction) mPressAction();
    eSounds::playButtonSound();
    return true;
}

bool eButtonBase::mouseMoveEvent(const eMouseEvent& e) {
    (void)e;
    return true;
}

bool eButtonBase::mouseEnterEvent(const eMouseEvent& e) {
    (void)e;
    mHover = true;
    return true;
}

bool eButtonBase::mouseLeaveEvent(const eMouseEvent& e) {
    (void)e;
    mHover = false;
    return true;
}
