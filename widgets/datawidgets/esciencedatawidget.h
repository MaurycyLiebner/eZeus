#ifndef ESCIENCEDATAWIDGET_H
#define ESCIENCEDATAWIDGET_H

#include "edatawidget.h"

class eScienceDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();

    void updateCoverage();
protected:
    void paintEvent(ePainter& p);
private:
    int mTime{0};
};

#endif // ESCIENCEDATAWIDGET_H
