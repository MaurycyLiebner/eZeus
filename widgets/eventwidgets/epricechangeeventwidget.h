#ifndef EPRICECHANGEEVENTWIDGET_H
#define EPRICECHANGEEVENTWIDGET_H

#include "../ewidget.h"

class ePriceChangeEvent;

class ePriceChangeEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(ePriceChangeEvent* const e);
};

#endif // EPRICECHANGEEVENTWIDGET_H
