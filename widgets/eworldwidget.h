#ifndef EWORLDWIDGET_H
#define EWORLDWIDGET_H

#include "ewidget.h"
#include "engine/egameboard.h"

class eWorldMenu;
class eWorldMapWidget;

class eWorldWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setBoard(eGameBoard* const board);
private:
    eWorldMenu* mWM = nullptr;
    eWorldMapWidget* mWMW = nullptr;
    eGameBoard* mBoard = nullptr;
};

#endif // EWORLDWIDGET_H
