#include "eworldwidget.h"

#include "eworldmenu.h"

void eWorldWidget::initialize() {
    mWM = new eWorldMenu(window());
    mWM->initialize();
    addWidget(mWM);
    mWM->align(eAlignment::right | eAlignment::top);
}

void eWorldWidget::setBoard(eGameBoard* const board) {
    mBoard = board;
}
