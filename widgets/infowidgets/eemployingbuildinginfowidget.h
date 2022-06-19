#ifndef EEMPLOYINGBUILDINGINFOWIDGET_H
#define EEMPLOYINGBUILDINGINFOWIDGET_H

#include "einfowidget.h"

class eEmployingBuilding;

class eEmployingBuildingInfoWidget : public eInfoWidget {
public:
    using eInfoWidget::eInfoWidget;

    void initialize(const std::string& title,
                    eEmployingBuilding* const b);
};

#endif // EEMPLOYINGBUILDINGINFOWIDGET_H
