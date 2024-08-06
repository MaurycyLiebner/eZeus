#ifndef EBASICCITYEVENTWIDGET_H
#define EBASICCITYEVENTWIDGET_H

#include "../ewidget.h"

class eBasicCityEvent;

class eBasicCityEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eBasicCityEvent* const e);
};

#endif // EBASICCITYEVENTWIDGET_H
