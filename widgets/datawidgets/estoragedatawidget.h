#ifndef ESTORAGEDATAWIDGET_H
#define ESTORAGEDATAWIDGET_H

#include "edatawidget.h"

#include "engine/eresourcetype.h"

class eGameBoard;
class eLabel;
class eViewModeButton;

class eStorageDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeDistribution = nullptr;

    std::vector<eLabel*> mResourceLabels;

    int mTime{0};
};

#endif // ESTORAGEDATAWIDGET_H
