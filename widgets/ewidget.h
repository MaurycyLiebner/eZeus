#ifndef EWIDGET_H
#define EWIDGET_H

#include <vector>

#include "epainter.h"
#include "emouseevent.h"

class eWidget {
public:
    eWidget(SDL_Renderer* const renderer);
    virtual ~eWidget();

    void move(const int x, const int y);
    void setX(const int x);
    void setY(const int y);
    void resize(const int w, const int h);

    void align(const eAlignment a);

    int x() const { return mX; }
    int y() const { return mY; }
    int width() const { return mWidth; }
    int height() const { return mHeight; }
    SDL_Rect rect() const { return {0, 0, mWidth, mHeight}; }

    eWidget* parent() const { return mParent; }

    bool contains(const int x, const int y) const;

    void mapToGlobal(int& x, int& y) const;
    void mapFromGlobal(int& x, int& y) const;
    void mapToParent(int& x, int& y) const;
    void mapFromParent(int& x, int& y) const;
    void mapTo(const eWidget* const to, int& x, int& y) const;
    void mapFrom(const eWidget* const from, int& x, int& y) const;

    void paint(ePainter& p);
    bool mousePress(const eMouseEvent& e);
    bool mouseRelease(const eMouseEvent& e);
    bool mouseMove(const eMouseEvent& e);
private:
    using TMouseEvent = bool (eWidget::*)(const eMouseEvent& e);
    eWidget* mouseEvent(const eMouseEvent& e, const TMouseEvent event);
public:
    void grabMouse();
    bool releaseMouse();
    bool isMouseGrabber();

    void grabKeyboard();
    bool releaseKeyboard();
    bool isKeyboardGrabber();

    void addWidget(eWidget* const w);
    void removeWidget(eWidget* const w);
private:
    void setParent(eWidget* const p);
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

    SDL_Renderer* renderer() const { return mRenderer; }
private:
    static eWidget* sWidgetUnderMouse;
    static eWidget* sMouseGrabber;
    static eWidget* sKeyboardGrabber;

    int mX = 0;
    int mY = 0;
    int mWidth = 0;
    int mHeight = 0;
    eWidget* mParent = nullptr;
    std::vector<eWidget*> mChildren;
    SDL_Renderer* const mRenderer;
};

#endif // EWIDGET_H
