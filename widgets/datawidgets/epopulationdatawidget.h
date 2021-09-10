#ifndef EPOPULATIONDATAWIDGET_H
#define EPOPULATIONDATAWIDGET_H

#include "../ewidget.h"

class eGameBoard;
class eLabel;
class eGameWidget;
class eViewModeButton;

class ePopulationDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const b);

    void setGameWidget(eGameWidget* const gw);
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
