#ifndef EOVERVIEWDATAWIDGET_H
#define EOVERVIEWDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;

class eOverviewDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize() override;

    void updateQuestButtons();
private:
    eViewModeButton* mSeeProblems = nullptr;
    eViewModeButton* mSeeRoads = nullptr;

    eWidget* mQuestButtons = nullptr;
};

#endif // EOVERVIEWDATAWIDGET_H
