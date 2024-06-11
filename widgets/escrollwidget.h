#ifndef ESCROLLWIDGET_H
#define ESCROLLWIDGET_H

#include "ewidget.h"

class eScrollWidget : public eWidget {
public:
    using eWidget::eWidget;

    void setScrollArea(eWidget* const w);
    eWidget* scrollArea() const { return mScrollArea; }

    void scrollUp();
    void scrollDown();
    void scrollToTheTop();
    void clampDY();
protected:
    void paintEvent(ePainter& p) override;

    bool keyPressEvent(const eKeyPressEvent& e) override;
    bool mouseWheelEvent(const eMouseWheelEvent& e) override;
private:
    int mDy = 0;

    eWidget* mScrollArea = nullptr;
};

#endif // ESCROLLWIDGET_H
