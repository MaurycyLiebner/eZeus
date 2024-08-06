#ifndef EWAGECHANGEEVENTWIDGET_H
#define EWAGECHANGEEVENTWIDGET_H

#include "../ewidget.h"

class eWageChangeEvent;

class eWageChangeEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eWageChangeEvent* const e);
};

#endif // EWAGECHANGEEVENTWIDGET_H
