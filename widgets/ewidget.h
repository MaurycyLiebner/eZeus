#ifndef EWIDGET_H
#define EWIDGET_H

#include <vector>

#include "epainter.h"
#include "emousepressevent.h"

class eWidget {
public:
    eWidget();
    virtual ~eWidget();

    void move(const int x, const int y);
    void resize(const int w, const int h);

    int x() const { return mX; }
    int y() const { return mY; }
    int width() const { return mWidth; }
    int height() const { return mHeight; }

    void paint(ePainter& p);
    bool mousePress(const eMouseEvent& e);
    bool mouseRelease(const eMouseEvent& e);
    bool mouseMove(const eMouseEvent& e);
protected:
    virtual void paintEvent(ePainter& p) {
        (void)p;
    }

    virtual bool mousePressEvent(const eMouseEvent& e) {
        (void)e;
        return false;
    }

    virtual bool mouseReleaseEvent(const eMouseEvent& e) {
        (void)e;
        return false;
    }

    virtual bool mouseEnterEvent(const eMouseEvent& e) {
        (void)e;
        return false;
    }

    virtual bool mouseLeaveEvent(const eMouseEvent& e) {
        (void)e;
        return false;
    }

    virtual bool mouseMoveEvent(const eMouseEvent& e) {
        (void)e;
        return false;
    }
private:
    using TMouseEvent = bool (eWidget::*)(const eMouseEvent& e);
    eWidget* mouseEvent(const eMouseEvent& e, const TMouseEvent event);

    static eWidget* sWidgetUnderMouse;

    int mX = 0;
    int mY = 0;
    int mWidth = 0;
    int mHeight = 0;
    std::vector<eWidget*> mChildren;
};

#endif // EWIDGET_H
