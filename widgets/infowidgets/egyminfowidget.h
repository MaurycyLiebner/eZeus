#ifndef EGYMINFOWIDGET_H
#define EGYMINFOWIDGET_H

#include "einfowidget.h"

class eGymInfoWidget : public eInfoWidget {
public:
    eGymInfoWidget(eMainWindow* const window);

    void initialize(const eAction& closeAction);

    void setCloseAction();
};

#endif // EGYMINFOWIDGET_H
