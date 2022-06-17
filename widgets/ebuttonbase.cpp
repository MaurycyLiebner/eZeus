#include "ebuttonbase.h"

#include "esounds.h"

void eButtonBase::setPressAction(const eAction& a) {
    mPressAction = a;
}

void eButtonBase::setMouseEnterAction(const eAction& a) {
    mEnterAction = a;
}

void eButtonBase::setMouseLeaveAction(const eAction& a) {
    mLeaveAction = a;
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
    if(mEnterAction) {
        mEnterAction();
    }
    mHover = true;
    return true;
}

bool eButtonBase::mouseLeaveEvent(const eMouseEvent& e) {
    (void)e;
    if(mLeaveAction) {
        mLeaveAction();
    }
    mHover = false;
    return true;
}
