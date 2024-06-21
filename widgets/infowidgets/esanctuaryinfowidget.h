#ifndef ESANCTUARYINFOWIDGET_H
#define ESANCTUARYINFOWIDGET_H

#include "eemployingbuildinginfowidget.h"

class eSanctuary;

class eSanctuaryInfoWidget : public eEmployingBuildingInfoWidget {
public:
    eSanctuaryInfoWidget(eMainWindow* const window);

    void initialize(eSanctuary* const s);
};

#endif // ESANCTUARYINFOWIDGET_H
