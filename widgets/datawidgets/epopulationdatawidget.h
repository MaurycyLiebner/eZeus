#ifndef EPOPULATIONDATAWIDGET_H
#define EPOPULATIONDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eMultiLineLabel;
class eGameWidget;
class eViewModeButton;

class ePopulationDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeSupplies = nullptr;

    eLabel* mNewcomersLabel = nullptr;
    eLabel* mVacLabel = nullptr;

    eLabel* mPeopleDirection = nullptr;

    eWidget* mImiLimitedW = nullptr;
    eLabel* mImiLimitedReason = nullptr;
    eWidget* mNewcomersW = nullptr;
};

#endif // EPOPULATIONDATAWIDGET_H
