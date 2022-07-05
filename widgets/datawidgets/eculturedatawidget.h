#ifndef ECULTUREDATAWIDGET_H
#define ECULTUREDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class eCultureDataWidget : public eDataWidget {
public:
    eCultureDataWidget(eGameBoard& board,
                       eMainWindow* const window);

    void initialize();

    void updateCoverage();
private:
    eWidget* createCoverageWidget(const std::string& gamesName,
                                  const std::string& disciplineName,
                                  eLabel** const clabel);

    eGameBoard& mBoard;

    eViewModeButton* mSeeActors = nullptr;
    eViewModeButton* mSeeAthletes = nullptr;
    eViewModeButton* mSeePhilosophers = nullptr;
    eViewModeButton* mSeeAllCulture = nullptr;

    eLabel* mPhilosophyCoverage = nullptr;
    eLabel* mAthleticsCoverage = nullptr;
    eLabel* mDramaCoverage = nullptr;
    eLabel* mAllCoverage = nullptr;
};

#endif // ECULTUREDATAWIDGET_H
