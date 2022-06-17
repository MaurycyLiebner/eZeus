#ifndef EOVERVIEWDATAWIDGET_H
#define EOVERVIEWDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;

class eOverviewDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeProblems = nullptr;
    eViewModeButton* mSeeRoads = nullptr;
};

#endif // EOVERVIEWDATAWIDGET_H
