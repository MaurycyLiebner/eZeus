#ifndef EECONOMICMILITARYCHANGEEVENTWIDGET_H
#define EECONOMICMILITARYCHANGEEVENTWIDGET_H

#include "../ewidget.h"

class eEconomicMilitaryChangeEventBase;

class eEconomicMilitaryChangeEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eEconomicMilitaryChangeEventBase* const e);
};

#endif // EECONOMICMILITARYCHANGEEVENTWIDGET_H
