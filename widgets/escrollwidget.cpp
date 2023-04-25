#include "escrollwidget.h"

void eScrollWidget::setScrollArea(eWidget* const w) {
    setMouseReceiver(w);
    mScrollArea = w;
    clampDY();
}

void eScrollWidget::scrollUp() {
    mDy -= 35;
    clampDY();
}

void eScrollWidget::scrollDown() {
    mDy += 35;
    clampDY();
}

void eScrollWidget::paintEvent(ePainter& p) {
    //p.fillRect(rect(), {255, 0, 0, 255});
    if(mScrollArea) {
        const auto r = rect();
        p.setClipRect(&r);

        p.translate(0, -mDy);
        mScrollArea->paint(p);
        p.translate(0, mDy);

        p.setClipRect(nullptr);
    }
}

bool eScrollWidget::keyPressEvent(const eKeyPressEvent& e) {
    if(e.key() == SDL_SCANCODE_UP) {
        scrollUp();
        return true;
    } else if(e.key() == SDL_SCANCODE_DOWN) {
        scrollDown();
        return true;
    }
    if(!mScrollArea) return false;
    return mScrollArea->keyPress(e.translated(0, -mDy));
}

bool eScrollWidget::mouseWheelEvent(const eMouseWheelEvent& e) {
    mDy -= 10*e.dy();
    clampDY();
    return true;
}

void eScrollWidget::clampDY() {
    if(mScrollArea) {
        const int sh = mScrollArea->height();
        const int h = height();
        if(h > sh) {
            mDy = 0;
        } else {
            const int maxH = sh - h;
            mDy = std::clamp(mDy, 0, maxH);
        }
        setMouseReceiverDXDY(0, mDy);
    } else {
        mDy = 0;
    }
}
