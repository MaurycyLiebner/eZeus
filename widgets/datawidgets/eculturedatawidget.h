#ifndef ECULTUREDATAWIDGET_H
#define ECULTUREDATAWIDGET_H

#include "../ewidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class eCultureDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setGameWidget(eGameWidget* const gw);
private:
    eViewModeButton* mSeeActors = nullptr;
    eViewModeButton* mSeeAthletes = nullptr;
    eViewModeButton* mSeePhilosophers = nullptr;
    eViewModeButton* mSeeAllCulture = nullptr;
};

#endif // ECULTUREDATAWIDGET_H
