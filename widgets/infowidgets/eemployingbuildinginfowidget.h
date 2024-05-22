#ifndef EEMPLOYINGBUILDINGINFOWIDGET_H
#define EEMPLOYINGBUILDINGINFOWIDGET_H

#include "einfowidget.h"

class eEmployingBuilding;

class eEmployingBuildingInfoWidget : public eInfoWidget {
public:
    using eInfoWidget::eInfoWidget;

    void initialize(const std::string& title,
                    eEmployingBuilding* const b);
    void initialize(const std::string& title,
                    const std::string& info,
                    const std::string& text,
                    eEmployingBuilding* const b,
                    const std::string& subText);

    void addEmploymentWidget(eEmployingBuilding* const b);
};

#endif // EEMPLOYINGBUILDINGINFOWIDGET_H
