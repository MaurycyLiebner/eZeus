#ifndef EHUSBANDRYDATAWIDGET_H
#define EHUSBANDRYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;

class eHusbandryDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeHusbandry = nullptr;

    eLabel* mCanSupportLabel = nullptr;
    eLabel* mOpinionLabel = nullptr;
    eLabel* mStoredFoodLabel = nullptr;
};

#endif // EHUSBANDRYDATAWIDGET_H
