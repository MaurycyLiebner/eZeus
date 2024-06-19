#include "erotatebutton.h"

#include "audio/esounds.h"
#include "elanguage.h"

eRotateButton::eRotateButton(eMainWindow* const window) :
    eLabel(window) {
    setNoPadding();
    updateTexture();
    fitContent();
}

void eRotateButton::setEnabled(const bool b) {
    mEnabled = b;
}

bool eRotateButton::enabled() const {
    return mEnabled;
}

bool eRotateButton::pressed() const {
    return mPressed;
}

bool eRotateButton::hovered() const {
    return mHover;
}

void eRotateButton::setDirection(const eWorldDirection dir) {
    mDirection = dir;
    updateTexture();
}

bool eRotateButton::mousePressEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    const auto b = e.button();
    if(b == eMouseButton::left) {
        mPressed = true;

        eSounds::playButtonSound();
        updateTexture();
        return true;
    } else {
        return false;
    }
}

bool eRotateButton::mouseReleaseEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    const auto b = e.button();
    if(b == eMouseButton::left) {
        mPressed = false;
        const auto oldD = mDirection;
        if(mHovered == eButtonHoverPortion::center) {
            mDirection = eWorldDirection::N;
        } else if(mHovered == eButtonHoverPortion::left) {
            if(mDirection == eWorldDirection::N) {
                mDirection = eWorldDirection::W;
            } else {
                const int i = static_cast<int>(mDirection) - 1;
                mDirection = static_cast<eWorldDirection>(i);
            }
        } else if(mHovered == eButtonHoverPortion::right) {
            if(mDirection == eWorldDirection::W) {
                mDirection = eWorldDirection::N;
            } else {
                const int i = static_cast<int>(mDirection) + 1;
                mDirection = static_cast<eWorldDirection>(i);
            }
        }
        if(mDirection == oldD) return true;
        if(mSetter) mSetter(mDirection);
        updateTexture();
        return true;
    } else {
        return false;
    }
}

bool eRotateButton::mouseMoveEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    (void)e;
    const int x = e.x();
    const int w = width()/3;
    if(x < w) {
        mHovered = eButtonHoverPortion::left;
        setTooltip(eLanguage::zeusText(68, 45));
    } else if(x < 2*w) {
        mHovered = eButtonHoverPortion::center;
        setTooltip(eLanguage::zeusText(68, 44));
    } else {
        mHovered = eButtonHoverPortion::right;
        setTooltip(eLanguage::zeusText(68, 46));
    }
    updateTexture();
    return true;
}

bool eRotateButton::mouseEnterEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    (void)e;
    mHover = true;
    updateTexture();
    return true;
}

bool eRotateButton::mouseLeaveEvent(const eMouseEvent& e) {
    if(!mEnabled) return false;
    (void)e;
    mHover = false;
    updateTexture();
    return true;
}

void eRotateButton::updateTexture() {
    int dx = 0;
    if(mEnabled) {
        if(!mHover) {
            dx = 0;
        } else if(mPressed) {
            if(mHovered == eButtonHoverPortion::center) {
                dx = 4;
            } else if(mHovered == eButtonHoverPortion::left) {
                dx = 5;
            } else if(mHovered == eButtonHoverPortion::right) {
                dx = 6;
            }
        } else { // !mPressed
            if(mHovered == eButtonHoverPortion::center) {
                dx = 1;
            } else if(mHovered == eButtonHoverPortion::left) {
                dx = 2;
            } else if(mHovered == eButtonHoverPortion::right) {
                dx = 3;
            }
        }
    } else {
        dx = 7;
    }
    const int ddx = static_cast<int>(mDirection);
    const int texId = 8*ddx + dx;

    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);

    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[iRes].fRotation;

    setTexture(coll.getTexture(texId));
}
