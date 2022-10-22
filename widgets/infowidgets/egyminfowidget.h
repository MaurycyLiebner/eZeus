#ifndef EGYMINFOWIDGET_H
#define EGYMINFOWIDGET_H

#include "eemployingbuildinginfowidget.h"

class eGymnasium;

class eGymInfoWidget : public eEmployingBuildingInfoWidget {
public:
    eGymInfoWidget(eMainWindow* const window);

    void initialize(eGymnasium* const gym);
};

#endif // EGYMINFOWIDGET_H
