#ifndef ESUPPLYDEMANDCHANGEEVENTWIDGET_H
#define ESUPPLYDEMANDCHANGEEVENTWIDGET_H

#include "../ewidget.h"

class eSupplyDemandChangeEvent;

class eSupplyDemandChangeEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eSupplyDemandChangeEvent* const e);
};

#endif // ESUPPLYDEMANDCHANGEEVENTWIDGET_H
