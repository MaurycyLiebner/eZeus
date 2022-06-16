#ifndef ECULTUREDATAWIDGET_H
#define ECULTUREDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class eCultureDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeActors = nullptr;
    eViewModeButton* mSeeAthletes = nullptr;
    eViewModeButton* mSeePhilosophers = nullptr;
    eViewModeButton* mSeeAllCulture = nullptr;
};

#endif // ECULTUREDATAWIDGET_H
