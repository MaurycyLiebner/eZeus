#ifndef ESCIENCEDATAWIDGET_H
#define ESCIENCEDATAWIDGET_H

#include "edatawidget.h"

class eLabel;

class eScienceDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();

    void updateCoverage();
protected:
    void paintEvent(ePainter& p);
private:
    eLabel* mAstronomyCoverage = nullptr;
    eLabel* mResearchCoverage = nullptr;
    eLabel* mLearningCoverage = nullptr;
    eLabel* mExhibits = nullptr;
};

#endif // ESCIENCEDATAWIDGET_H
