#ifndef EAGORAINFOWIDGET_H
#define EAGORAINFOWIDGET_H

#include "eemployingbuildinginfowidget.h"

#include "buildings/eagorabase.h"

class eAgoraInfoWidget : public eEmployingBuildingInfoWidget {
public:
    eAgoraInfoWidget(eMainWindow* const window);

    void initialize(eAgoraBase* const a);
};

#endif // EAGORAINFOWIDGET_H
