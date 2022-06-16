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

    void setBoard(eGameBoard* const b);
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeDistribution = nullptr;

    eGameBoard* mBoard = nullptr;

    std::vector<eLabel*> mResourceLabels;

    int mTime{0};
};

#endif // ESTORAGEDATAWIDGET_H
