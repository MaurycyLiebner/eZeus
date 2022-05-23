#include "eworldwidget.h"

#include "eworldmenu.h"
#include "eworldmapwidget.h"

void eWorldWidget::initialize() {
    mWM = new eWorldMenu(window());
    mWM->initialize();
    addWidget(mWM);
    mWM->align(eAlignment::right | eAlignment::top);

    mWMW = new eWorldMapWidget(window());
    mWMW->initialize();
    addWidget(mWMW);
    mWMW->align(eAlignment::center);
    mWMW->setX((width() - mWM->width() - mWMW->width())/2);
}

void eWorldWidget::setBoard(eGameBoard* const board) {
    mBoard = board;
    mWMW->setBoard(board ? &board->getWorldBoard() : nullptr);
}
