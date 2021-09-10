#ifndef EHYGIENESAFETYDATAWIDGET_H
#define EHYGIENESAFETYDATAWIDGET_H

#include "../ewidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class eHygieneSafetyDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setGameWidget(eGameWidget* const gw);
private:
    eViewModeButton* mSeeWater = nullptr;
    eViewModeButton* mSeeHygiene = nullptr;
    eViewModeButton* mSeeHazards = nullptr;
    eViewModeButton* mSeeUnrest = nullptr;
};

#endif // EHYGIENESAFETYDATAWIDGET_H
