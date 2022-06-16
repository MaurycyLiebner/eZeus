#ifndef EPOPULATIONDATAWIDGET_H
#define EPOPULATIONDATAWIDGET_H

#include "edatawidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class ePopulationDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();

    void setBoard(eGameBoard* const b);
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeSupplies = nullptr;
    eGameBoard* mBoard = nullptr;

    eLabel* mPopLabel = nullptr;
    eLabel* mVacLabel = nullptr;

    int mTime{0};
};

#endif // EPOPULATIONDATAWIDGET_H
