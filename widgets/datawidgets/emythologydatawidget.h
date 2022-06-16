#ifndef EMYTHOLOGYDATAWIDGET_H
#define EMYTHOLOGYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;

class eMythologyDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeImmortals = nullptr;
};

#endif // EMYTHOLOGYDATAWIDGET_H
