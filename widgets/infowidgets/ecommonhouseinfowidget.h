#ifndef ECOMMONHOUSEINFOWIDGET_H
#define ECOMMONHOUSEINFOWIDGET_H

#include "einfowidget.h"

class eSmallHouse;

class eCommonHouseInfoWidget : public eInfoWidget {
public:
    eCommonHouseInfoWidget(eMainWindow* const window);

    void initialize(eSmallHouse* const house);
};

#endif // ECOMMONHOUSEINFOWIDGET_H
