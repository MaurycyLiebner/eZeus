#ifndef EHYGIENESAFETYDATAWIDGET_H
#define EHYGIENESAFETYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class eHygieneSafetyDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeWater = nullptr;
    eViewModeButton* mSeeHygiene = nullptr;
    eViewModeButton* mSeeHazards = nullptr;
    eViewModeButton* mSeeUnrest = nullptr;
};

#endif // EHYGIENESAFETYDATAWIDGET_H
