#ifndef EHUSBANDRYDATAWIDGET_H
#define EHUSBANDRYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;

class eHusbandryDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeHusbandry = nullptr;
};

#endif // EHUSBANDRYDATAWIDGET_H
