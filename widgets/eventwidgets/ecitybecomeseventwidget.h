#ifndef ECITYBECOMESEVENTWIDGET_H
#define ECITYBECOMESEVENTWIDGET_H

#include "../ewidget.h"

class eCityBecomesEvent;

class eCityBecomesEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eCityBecomesEvent* const e);
};

#endif // ECITYBECOMESEVENTWIDGET_H
