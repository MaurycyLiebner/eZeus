#ifndef EOVERVIEWDATAWIDGET_H
#define EOVERVIEWDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;
class eOverviewEntry;

class eOverviewDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize() override;

    void updateRequestButtons();
protected:
    void paintEvent(ePainter& p) override;
private:
    void addGodQuests();
    void addCityRequests();

    eViewModeButton* mSeeProblems = nullptr;
    eViewModeButton* mSeeRoads = nullptr;

    eWidget* mQuestButtons = nullptr;

    eOverviewEntry* mPopularity = nullptr;
    eOverviewEntry* mFoodLevel = nullptr;
    eOverviewEntry* mUnemployment = nullptr;
    eOverviewEntry* mHygiene = nullptr;
    eOverviewEntry* mUnrest = nullptr;
    eOverviewEntry* mFinances = nullptr;
};

#endif // EOVERVIEWDATAWIDGET_H
