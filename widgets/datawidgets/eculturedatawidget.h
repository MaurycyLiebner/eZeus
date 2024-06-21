#ifndef ECULTUREDATAWIDGET_H
#define ECULTUREDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;

class eCultureDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();

    void updateCoverage();
protected:
    void paintEvent(ePainter& p);
private:
    eWidget* createCoverageWidget(const int gamesName,
                                  const int disciplineName,
                                  eLabel** const clabel);

    eLabel* mPhilosophyCoverage = nullptr;
    eLabel* mAthleticsCoverage = nullptr;
    eLabel* mDramaCoverage = nullptr;
    eLabel* mAllCoverage = nullptr;

    int mTime{0};
};

#endif // ECULTUREDATAWIDGET_H
