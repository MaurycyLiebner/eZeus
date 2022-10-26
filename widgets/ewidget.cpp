#include "ewidget.h"

#include "emainwindow.h"

#include <algorithm>

#include "evectorhelpers.h"

eWidget* eWidget::sWidgetUnderMouse = nullptr;
eWidget* eWidget::sLastPressed = nullptr;
eWidget* eWidget::sMouseGrabber = nullptr;
eWidget* eWidget::sKeyboardGrabber = nullptr;

#define ReverseFor(i, cont) for(i = cont.begin(); i < cont.end(); i++)

eWidget::eWidget(eMainWindow* const window) :
    mWindow(window) {
    mPadding = resolution().largePadding();
}

eWidget::~eWidget() {
    removeChildren();
    clearWidgetPointers();
}

void eWidget::iResAndMult(int& iRes, int& mult) const {
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    iRes = static_cast<int>(uiScale);
    mult = iRes + 1;
}

SDL_Renderer* eWidget::renderer() const {
    return mWindow->renderer();
}

eResolution eWidget::resolution() const {
    return mWindow->resolution();
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
}

void eWidget::setWidth(const int w) {
    resize(w, height());
}

void eWidget::setHeight(const int h) {
    resize(width(), h);
}

void eWidget::setPadding(const int padding) {
    mPadding = padding;
}

void eWidget::fitContent() {
    int w;
    int h;
    sizeHint(w, h);
    resize(w + 2*mPadding, h + 2*mPadding);
}

void eWidget::show() {
    mVisible = true;
}

void eWidget::hide() {
    mVisible = false;
    clearWidgetPointers();
}

void eWidget::setVisible(const bool v) {
    if(v) show();
    else hide();
}

void eWidget::clearWidgetPointers() {
    if(sWidgetUnderMouse == this) sWidgetUnderMouse = nullptr;
    if(sLastPressed == this) sLastPressed = nullptr;
    if(sMouseGrabber == this) sMouseGrabber = nullptr;
    if(sKeyboardGrabber == this) sKeyboardGrabber = nullptr;
}

void eWidget::setHugePadding() {
    mPadding = resolution().hugePadding();
}

void eWidget::setLargePadding() {
    mPadding = resolution().largePadding();
}

void eWidget::setSmallPadding() {
    mPadding = resolution().smallPadding();
}

void eWidget::setTinyPadding() {
    mPadding = resolution().tinyPadding();
}

void eWidget::setVeryTinyPadding() {
    mPadding = resolution().veryTinyPadding();
}

void eWidget::setVeryVeryTinyPadding() {
    mPadding = resolution().veryVeryTinyPadding();
}

void eWidget::setNoPadding() {
    mPadding = 0;
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
        if(!w->visible()) continue;
        w->paint(p);
    }

    p.restore();
}

bool eWidget::keyPress(const eKeyPressEvent& e) {
    eWidget* override = nullptr;
    if(sKeyboardGrabber) override = sKeyboardGrabber;
    else override = sLastPressed;
    if(override) {
        int ex = e.x();
        int ey = e.y();
        mapTo(override, ex, ey);
        const auto ee = e.withPosition(ex, ey);
        override->keyPressEvent(ee);
        return true;
    }
    const auto handler = mouseEvent(e, &eWidget::keyPressEvent);
    return handler;
}

bool eWidget::mousePress(const eMouseEvent& e) {
    eWidget* override = nullptr;
    if(sMouseGrabber) override = sMouseGrabber;
    else override = sLastPressed;
    if(override) {
        int ex = e.x();
        int ey = e.y();
        mapTo(override, ex, ey);
        const auto ee = e.withPosition(ex, ey);
        override->mousePressEvent(ee);
        return true;
    }
    sLastPressed = mouseEvent(e, &eWidget::mousePressEvent, true);
    return sLastPressed;
}

bool eWidget::mouseRelease(const eMouseEvent& e) {
    eWidget* override = nullptr;
    if(sMouseGrabber) override = sMouseGrabber;
    else override = sLastPressed;
    sLastPressed = nullptr;
    if(override) {
        int ex = e.x();
        int ey = e.y();
        mapTo(override, ex, ey);
        const auto ee = e.withPosition(ex, ey);
        override->mouseReleaseEvent(ee);
        override->mouseLeaveEvent(ee);
        override = nullptr;
        return mouseEvent(e, &eWidget::mouseEnterEvent, true);
        return true;
    }
    return mouseEvent(e, &eWidget::mouseReleaseEvent, true);
}

bool eWidget::mouseMove(const eMouseEvent& e) {
    eWidget* override = nullptr;
    if(sMouseGrabber) override = sMouseGrabber;
    else override = sLastPressed;
    if(override) {
        int ex = e.x();
        int ey = e.y();
        mapTo(override, ex, ey);
        const auto we = e.withPosition(ex, ey);
        const auto r = override->mouseMoveEvent(we);
        return r;
    } else {
        const auto w = mouseEvent(e, &eWidget::mouseMoveEvent, true);
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

bool eWidget::mouseWheel(const eMouseWheelEvent& e) {
    eWidget* override = nullptr;
    if(sMouseGrabber) override = sMouseGrabber;
    else override = sLastPressed;
    if(override) {
        int ex = e.x();
        int ey = e.y();
        mapTo(override, ex, ey);
        const auto ee = e.withPosition(ex, ey);
        override->mouseWheelEvent(ee);
        return true;
    }
    return mouseEvent(e, &eWidget::mouseWheelEvent);
}

void eWidget::deleteLater() {
    if(mDeleteLater) return;
    if(mParent) mParent->removeWidget(this);
    mWindow->addSlot([this]() {
        delete this;
    });
    mDeleteLater = true;
}

eWidget* eWidget::lastAncestor() {
    eWidget* p = this;
    while(p->parent()) {
        p = p->parent();
    }
    return p;
}

void eWidget::removeChildren() {
    for(const auto w : mChildren) {
        delete w;
    }
    mChildren.clear();
}

template <typename T>
eWidget* eWidget::mouseEvent(const T& e, const TMouseEvent<T> event,
                             const bool overwrite) {
    if(mMouseReceiver && overwrite) {
        return mMouseReceiver->mouseEvent(e, event);
    }
    if(!contains(e.x(), e.y())) return nullptr;
    for(auto w = mChildren.rbegin(); w != mChildren.rend(); w++) {
        const auto& ww = *w;
        if(!ww->visible()) continue;
        const auto we = e.translated(-ww->x(), -ww->y());
        const auto www = ww->mouseEvent(we, event, overwrite);
        if(www) return www;
    }
    const bool r = (this->*event)(e);
    if(r) return this;
    return nullptr;
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

void eWidget::prependWidget(eWidget* const w) {
    mChildren.insert(mChildren.begin(), w);
    w->mParent = this;
}

void eWidget::addWidget(eWidget* const w) {
    mChildren.push_back(w);
    w->mParent = this;
}

void eWidget::removeWidget(eWidget* const w) {
    const bool r = eVectorHelpers::remove(mChildren, w);
    if(r) w->mParent = nullptr;
}

void eWidget::stackVertically() {
    int wsHeight = 0;
    for(const auto w : mChildren) {
        wsHeight += w->height();
    }
    int y = 0;
    for(const auto w : mChildren) {
        w->setY(y);
        y += w->height();
    }
}

void eWidget::layoutVertically() {
    const int spaces = mChildren.size() + 1;
    int wsHeight = 0;
    for(const auto w : mChildren) {
        wsHeight += w->height();
    }
    const int space = (height() - wsHeight)/spaces;
    int y = space;
    for(const auto w : mChildren) {
        w->setY(y);
        y += w->height() + space;
    }
}

void eWidget::stackHorizontally() {
    int wsWidth = 0;
    for(const auto w : mChildren) {
        wsWidth += w->width();
    }
    int x = 0;
    for(const auto w : mChildren) {
        w->setX(x);
        x += w->width();
    }
}

void eWidget::layoutHorizontally() {
    const int spaces = mChildren.size() + 1;
    int wsWidth = 0;
    for(const auto w : mChildren) {
        wsWidth += w->width();
    }
    const int space = (width() - wsWidth)/spaces;
    int x = space;
    for(const auto w : mChildren) {
        w->setX(x);
        x += w->width() + space;
    }
}

void eWidget::setMouseReceiver(eWidget* const w) {
    mMouseReceiver = w;
}

void eWidget::sizeHint(int& w, int& h) {
    w = 0;
    h = 0;
    for(const auto c : mChildren) {
        if(!c->visible()) continue;
        w = std::max(w, c->x() + c->width());
        h = std::max(h, c->y() + c->height());
    }
}

void eWidget::paintEvent(ePainter& p) {
    (void)p;
    //p.drawRect(rect(), {0, 0, 0, 255}, 1);
}
