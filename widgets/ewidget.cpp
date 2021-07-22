#include "ewidget.h"

eWidget* eWidget::sWidgetUnderMouse = nullptr;

eWidget::eWidget() {

}

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

void eWidget::resize(const int w, const int h) {
    mWidth = w;
    mHeight = h;
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
    return mouseEvent(e, &eWidget::mousePressEvent);
}

bool eWidget::mouseRelease(const eMouseEvent& e) {
    return mouseEvent(e, &eWidget::mouseReleaseEvent);
}

bool eWidget::mouseMove(const eMouseEvent& e) {
    const auto w = mouseEvent(e, &eWidget::mouseMoveEvent);
    if(w == sWidgetUnderMouse) return w;
    if(sWidgetUnderMouse) {
        sWidgetUnderMouse->mouseLeaveEvent(e);
    }
    sWidgetUnderMouse = w;
    if(w) {
        w->mouseEnterEvent(e);
    }
    return w;
}

eWidget* eWidget::mouseEvent(const eMouseEvent& e, const TMouseEvent event) {
    if(e.x() < 0 || e.y() < 0) return nullptr;
    if(e.x() > mWidth || e.y() > mHeight) return nullptr;
    for(const auto w : mChildren) {
        const auto we = e.translated(-w->x(), -w->y());
        const bool r = w->mouseEvent(we, event);
        if(r) return w;
    }
    const bool r = (this->*event)(e);
    if(r) return this;
    return nullptr;
}
