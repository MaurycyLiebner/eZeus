#ifndef ECOMMONHOUSEINFOWIDGET_H
#define ECOMMONHOUSEINFOWIDGET_H

#include "einfowidget.h"

class eSmallHouse;

class eCommonHouseInfoWidget : public eInfoWidget {
public:
    using eInfoWidget::eInfoWidget;

    void initialize(eSmallHouse* const house);
};

#endif // ECOMMONHOUSEINFOWIDGET_H
