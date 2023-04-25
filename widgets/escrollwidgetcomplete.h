#ifndef ESCROLLWIDGETCOMPLETE_H
#define ESCROLLWIDGETCOMPLETE_H

#include "ewidget.h"

class eScrollBar;
class eScrollWidget;

class eScrollWidgetComplete : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();
    void setScrollArea(eWidget* const widget);

    int listWidth() const;
private:
    eScrollBar* mSB = nullptr;
    eScrollWidget* mSW = nullptr;
};

#endif // ESCROLLWIDGETCOMPLETE_H
