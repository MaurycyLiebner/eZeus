#ifndef EPOPULATIONDATAWIDGET_H
#define EPOPULATIONDATAWIDGET_H

#include "../ewidget.h"

class eGameBoard;
class eLabel;

class ePopulationDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const b);
protected:
    void paintEvent(ePainter& p);
private:
    eGameBoard* mBoard = nullptr;

    eLabel* mPopLabel = nullptr;
    eLabel* mVacLabel = nullptr;
    eLabel* mSetLabel = nullptr;

    int mTime{0};
};

#endif // EPOPULATIONDATAWIDGET_H
