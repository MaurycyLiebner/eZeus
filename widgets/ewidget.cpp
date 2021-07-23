#include "ewidget.h"

#include "elayout.h"

#include <bits/stdc++.h>

eWidget* eWidget::sWidgetUnderMouse = nullptr;
eWidget* eWidget::sMouseGrabber = nullptr;
eWidget* eWidget::sKeyboardGrabber = nullptr;

eWidget::eWidget(SDL_Renderer* const renderer) :
    mRenderer(renderer) {}

eWidget::~eWidget() {
    for(const auto w : mChildren) {
        delete w;
    }
    if(sWidgetUnderMouse == this) sWidgetUnderMouse = nullptr;
}

void eWidget::move(const int x, const int y) {
    mX = x;
    mY = y;
}

void eWidget::setX(const int x) {
    mX = x;
}

void eWidget::setY(const int y) {
    mY = y;
}

void eWidget::resize(const int w, const int h) {
    mWidth = w;
    mHeight = h;
    if(mParent) {
        mParent->updateLayout();
    }
    updateLayout();
}

void eWidget::align(const eAlignment a) {
    if(!mParent) return;
    if(static_cast<bool>(a & eAlignment::left)) {
        setX(0);
    } else if(static_cast<bool>(a & eAlignment::right)) {
        setX(mParent->width() - width());
    } else if(static_cast<bool>(a & eAlignment::hcenter)) {
        setX((mParent->width() - width())/2);
    }

    if(static_cast<bool>(a & eAlignment::top)) {
        setY(0);
    } else if(static_cast<bool>(a & eAlignment::bottom)) {
        setY(mParent->height() - height());
    } else if(static_cast<bool>(a & eAlignment::vcenter)) {
        setY((mParent->height() - height())/2);
    }
}

bool eWidget::contains(const int x, const int y) const {
    if(x < 0 || y < 0) return false;
    if(x > mWidth || y > mHeight) return false;
    return true;
}

void eWidget::mapToGlobal(int& x, int& y) const {
    int gx = 0;
    int gy = 0;
    mapFromGlobal(gx, gy);
    x -= gx;
    y -= gy;
}

void eWidget::mapFromGlobal(int& x, int& y) const {
    const eWidget* p = this;
    while(p) {
        p->mapFromParent(x, y);
        p = p->parent();
    }
}

void eWidget::mapToParent(int& x, int& y) const {
    x += mX;
    y += mY;
}

void eWidget::mapFromParent(int& x, int& y) const {
    x -= mX;
    y -= mY;
}

void eWidget::mapTo(const eWidget* const to, int& x, int& y) const {
    to->mapFrom(this, x, y);
}

void eWidget::mapFrom(const eWidget* const from, int& x, int& y) const {
    if(from == this) return;
    int gfx = 0;
    int gfy = 0;
    from->mapToGlobal(gfx, gfy);

    int gtx = 0;
    int gty = 0;
    this->mapToGlobal(gtx, gty);

    x += gfx - gtx;
    y += gfy - gty;
}

void eWidget::paint(ePainter& p) {
    p.save();
    p.translate(mX, mY);

    p.save();
    paintEvent(p);
    p.restore();

    for(const auto w : mChildren) {
        w->paint(p);
    }

    p.restore();
}

bool eWidget::mousePress(const eMouseEvent& e) {
    if(sMouseGrabber) {
        int ex = e.x();
        int ey = e.y();
        mapTo(sMouseGrabber, ex, ey);
        const auto ee = e.withPosition(ex, ey);
        sMouseGrabber->mousePressEvent(ee);
        return true;
    }
    sMouseGrabber = mouseEvent(e, &eWidget::mousePressEvent);
    return sMouseGrabber;
}

bool eWidget::mouseRelease(const eMouseEvent& e) {
    if(sMouseGrabber) {
        int ex = e.x();
        int ey = e.y();
        mapTo(sMouseGrabber, ex, ey);
        const auto ee = e.withPosition(ex, ey);
        sMouseGrabber->mouseReleaseEvent(ee);
        sMouseGrabber->mouseLeaveEvent(ee);
        sMouseGrabber = nullptr;
        return mouseEvent(e, &eWidget::mouseEnterEvent);
        return true;
    }
    return mouseEvent(e, &eWidget::mouseReleaseEvent);
}

bool eWidget::mouseMove(const eMouseEvent& e) {
    if(sMouseGrabber) {
        int ex = e.x();
        int ey = e.y();
        mapTo(sMouseGrabber, ex, ey);
        const auto we = e.withPosition(ex, ey);
        const auto r = sMouseGrabber->mouseMoveEvent(we);
        return r;
    } else {
        const auto w = mouseEvent(e, &eWidget::mouseMoveEvent);
        if(w == sWidgetUnderMouse) return w;
        if(sWidgetUnderMouse) {
            sWidgetUnderMouse->mouseLeaveEvent(e);
        }
        if(w) {
            w->mouseEnterEvent(e);
        }
        sWidgetUnderMouse = w;
        return w;
    }
}

void eWidget::grabMouse() {
    if(isMouseGrabber()) return;
    if(sMouseGrabber) {
        sMouseGrabber->releaseMouse();
    }
    sMouseGrabber = this;
}

bool eWidget::releaseMouse() {
    if(!isMouseGrabber()) {
        return false;
    }
    sMouseGrabber = nullptr;
    return true;
}

bool eWidget::isMouseGrabber() {
    return sMouseGrabber == this;
}

void eWidget::grabKeyboard() {
    if(isKeyboardGrabber()) return;
    if(sKeyboardGrabber) {
        sKeyboardGrabber->releaseKeyboard();
    }
    sKeyboardGrabber = this;
}

bool eWidget::releaseKeyboard() {
    if(!isKeyboardGrabber()) {
        return false;
    }
    sKeyboardGrabber = nullptr;
    return true;
}

bool eWidget::isKeyboardGrabber() {
    return sKeyboardGrabber == this;
}

void eWidget::setLayout(eLayout* const layout) {
    if(mLayout) delete mLayout;
    mLayout = layout;
    updateLayout();
}

void eWidget::updateLayout() {
    if(!mLayout) return;
    mLayout->layoutWidgets(rect(), mChildren);
}

eWidget* eWidget::mouseEvent(
        const eMouseEvent& e, const TMouseEvent event) {
    if(!contains(e.x(), e.y())) return nullptr;
    for(const auto w : mChildren) {
        const auto we = e.translated(-w->x(), -w->y());
        const bool r = w->mouseEvent(we, event);
        if(r) return w;
    }
    const bool r = (this->*event)(e);
    if(r) return this;
    return nullptr;
}

void eWidget::addWidget(eWidget* const w) {
    mChildren.push_back(w);
    w->setParent(this);
    updateLayout();
}

void eWidget::removeWidget(eWidget* const w) {
    std::remove(mChildren.begin(), mChildren.end(), w);
    w->setParent(nullptr);
    updateLayout();
}

void eWidget::setParent(eWidget* const p) {
    if(p == mParent) return;
    if(mParent) {
        mParent->removeWidget(this);
    }
    mParent = p;
}

