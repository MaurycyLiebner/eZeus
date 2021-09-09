#ifndef ESTORAGEDATAWIDGET_H
#define ESTORAGEDATAWIDGET_H

#include "../ewidget.h"

#include "engine/eresourcetype.h"

class eGameBoard;
class eLabel;

class eStorageDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const b);
protected:
    void paintEvent(ePainter& p);
private:
    eGameBoard* mBoard = nullptr;

    std::vector<eLabel*> mResourceLabels;

    int mTime{0};
};

#endif // ESTORAGEDATAWIDGET_H
