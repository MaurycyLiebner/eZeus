#ifndef EEMPLOYMENTDATAWIDGET_H
#define EEMPLOYMENTDATAWIDGET_H

#include "edatawidget.h"

#include "engine/ewagerate.h"

class eGameBoard;
class eLabel;

class eEmploymentDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();

protected:
    void paintEvent(ePainter& p);
    void openMoreInfoWiget();
private:
    void setWageRate(const eWageRate wr);

    eViewModeButton* mSeeIndustry = nullptr;

    eLabel* mPensionsLabel = nullptr;

    eLabel* mWorkforceLabel = nullptr;

    eWidget* mUnemployedWidget = nullptr;
    eLabel* mUnemployedNLabel = nullptr;

    eWidget* mVacanciesWidget = nullptr;
    eLabel* mVacanciesNLabel = nullptr;

    eLabel* mWageLabel = nullptr;

    eWageRate mWageRate{eWageRate::normal};
};

#endif // EEMPLOYMENTDATAWIDGET_H
