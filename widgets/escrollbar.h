#ifndef ESCROLLBAR_H
#define ESCROLLBAR_H

#include "ewidget.h"

class eScrollWidget;

class eScrollBar : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const int height);

    void setScrollWidget(eScrollWidget* const sw);

    void scrollUp();
    void scrollDown();
private:
    eScrollWidget* mSw = nullptr;
};

#endif // ESCROLLBAR_H
