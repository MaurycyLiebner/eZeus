#ifndef EEMPLOYMENTDATAWIDGET_H
#define EEMPLOYMENTDATAWIDGET_H

#include "edatalabel.h"

class eGameBoard;
class eLabel;

class eEmploymentDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const b);
protected:
    void paintEvent(ePainter& p);
private:
    eGameBoard* mBoard = nullptr;

    eLabel* mPensionsLabel = nullptr;

    eLabel* mWorkforceLabel = nullptr;

    eDataLabel* mUnemployedLabel = nullptr;
    eLabel* mUnemployedNLabel = nullptr;

    eDataLabel* mVacanciesLabel = nullptr;
    eLabel* mVacanciesNLabel = nullptr;

    int mTime{0};
};

#endif // EEMPLOYMENTDATAWIDGET_H
