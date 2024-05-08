#ifndef EHYGIENESAFETYDATAWIDGET_H
#define EHYGIENESAFETYDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eMultiLineLabel;
class eGameWidget;
class eViewModeButton;

class eHygieneSafetyDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeWater = nullptr;
    eViewModeButton* mSeeHygiene = nullptr;
    eViewModeButton* mSeeHazards = nullptr;
    eViewModeButton* mSeeUnrest = nullptr;

    eLabel* mHygieneLabel = nullptr;
    eMultiLineLabel* mUnrestLabel = nullptr;

    int mTime{0};
};

#endif // EHYGIENESAFETYDATAWIDGET_H
