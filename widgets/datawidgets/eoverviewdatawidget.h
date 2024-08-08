#ifndef EOVERVIEWDATAWIDGET_H
#define EOVERVIEWDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;
class eOverviewEntry;
class eMiniMap;

class eOverviewDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize() override;

    void shown() override;

    void updateRequestButtons();
    void setMap(eMiniMap* const map);
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

    eMiniMap* mMap = nullptr;
};

#endif // EOVERVIEWDATAWIDGET_H
