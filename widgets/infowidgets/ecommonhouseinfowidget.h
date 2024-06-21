#ifndef ECOMMONHOUSEINFOWIDGET_H
#define ECOMMONHOUSEINFOWIDGET_H

#include "einfowidget.h"

class eHouseBase;

class eCommonHouseInfoWidget : public eInfoWidget {
public:
    eCommonHouseInfoWidget(eMainWindow* const window);

    void initialize(eHouseBase* const house);
};

#endif // ECOMMONHOUSEINFOWIDGET_H
