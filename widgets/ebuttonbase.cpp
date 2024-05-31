#include "ebuttonbase.h"

#include "audio/esounds.h"

void eButtonBase::setPressAction(const eAction& a) {
    mPressAction = a;
}

void eButtonBase::setMouseEnterAction(const eAction& a) {
    mEnterAction = a;
}

void eButtonBase::setMouseLeaveAction(const eAction& a) {
    mLeaveAction = a;
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
    if(!mEnabled) return false;
    if(e.button() == eMouseButton::left) {
        mPressed = true;
        return true;
    } else {
        return false;
    }
}

bool eButtonBase::mouseReleaseEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    if(e.button() == eMouseButton::left) {
        mPressed = false;
        if(mPressAction) mPressAction();
        eSounds::playButtonSound();
        return true;
    } else {
        return false;
    }
}

bool eButtonBase::mouseMoveEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    (void)e;
    return true;
}

bool eButtonBase::mouseEnterEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    (void)e;
    if(mEnterAction) {
        mEnterAction();
    }
    mHover = true;
    return true;
}

bool eButtonBase::mouseLeaveEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    (void)e;
    if(mLeaveAction) {
        mLeaveAction();
    }
    mHover = false;
    return true;
}
