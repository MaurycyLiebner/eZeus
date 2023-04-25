#ifndef EWIDGET_H
#define EWIDGET_H

#include <vector>
#include <functional>

#include "epainter.h"
#include "emouseevent.h"
#include "eresolution.h"

class eMainWindow;
class eLayout;

using eAction = std::function<void()>;

class eWidget {
public:
    eWidget(eMainWindow* const window);
protected:
    virtual ~eWidget();

    void iResAndMult(int& iRes, int& mult) const;
public:
    void move(const int x, const int y);
    void setX(const int x);
    void setY(const int y);
    void resize(const int w, const int h);
    void setWidth(const int w);
    void setHeight(const int h);
    void setPadding(const int padding);
    void fitContent();
    void fitHeight();
    void show();
    void hide();
    void setVisible(const bool v);
    void clearWidgetPointers();

    void setHugePadding();
    void setLargePadding();
    void setSmallPadding();
    void setTinyPadding();
    void setVeryTinyPadding();
    void setVeryVeryTinyPadding();
    void setNoPadding();

    void align(const eAlignment a);

    int x() const { return mX; }
    int y() const { return mY; }
    int width() const { return mWidth; }
    int height() const { return mHeight; }
    int padding() const { return mPadding; }
    SDL_Rect rect() const { return {0, 0, mWidth, mHeight}; }
    bool visible() const { return mVisible; }

    eWidget* parent() const { return mParent; }

    bool contains(const int x, const int y) const;

    void mapToGlobal(int& x, int& y) const;
    void mapFromGlobal(int& x, int& y) const;
    void mapToParent(int& x, int& y) const;
    void mapFromParent(int& x, int& y) const;
    void mapTo(const eWidget* const to, int& x, int& y) const;
    void mapFrom(const eWidget* const from, int& x, int& y) const;

    void paint(ePainter& p);
    bool keyPress(const eKeyPressEvent& e);
    bool mousePress(const eMouseEvent& e);
    bool mouseRelease(const eMouseEvent& e);
    bool mouseMove(const eMouseEvent& e);
    bool mouseWheel(const eMouseWheelEvent& e);

    const std::vector<eWidget*>& children() const { return mChildren; }

    void deleteLater();

    eWidget* lastAncestor();

    void removeChildren();
private:
    template <typename T>
    using TMouseEvent = bool (eWidget::*)(const T& e);
    template <typename T>
    eWidget* mouseEvent(const T& e, const TMouseEvent<T> event,
                        const bool overwrite = false);
public:
    void grabMouse();
    bool releaseMouse();
    bool isMouseGrabber();

    void grabKeyboard();
    bool releaseKeyboard();
    bool isKeyboardGrabber();

    void prependWidget(eWidget* const w);
    void addWidget(eWidget* const w);
    void removeWidget(eWidget* const w);
    void removeAllWidgets();

    void stackVertically();
    void layoutVertically();
    void stackHorizontally();
    void layoutHorizontally();
    void layoutHorizontallyWithoutSpaces();

    void setMouseReceiver(eWidget* const w);
    void setMouseReceiverDXDY(const int dx, const int dy);
protected:
    virtual void sizeHint(int& w, int& h);

    virtual void paintEvent(ePainter& p);

    virtual bool keyPressEvent(const eKeyPressEvent& e) {
        (void)e;
        return false;
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

    virtual bool mouseWheelEvent(const eMouseWheelEvent& e) {
        (void)e;
        return false;
    }

    SDL_Renderer* renderer() const;
    eMainWindow* window() const { return mWindow; }
    eResolution resolution() const;
private:
    static eWidget* sWidgetUnderMouse;
    static eWidget* sLastPressed;
    static eWidget* sMouseGrabber;
    static eWidget* sKeyboardGrabber;

    int mX = 0;
    int mY = 0;
    int mWidth = 0;
    int mHeight = 0;
    int mPadding = 0;
    bool mVisible = true;
    bool mDeleteLater = false;
    eWidget* mParent = nullptr;
    std::vector<eWidget*> mChildren;
    eMainWindow* const mWindow;

    eWidget* mMouseReceiver = nullptr;
    int mMouseReceiverDx = 0;
    int mMouseReceiverDy = 0;
};

#endif // EWIDGET_H
