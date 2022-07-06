#include "edatawidget.h"

#include "eviewmodebutton.h"

eDataWidget::eDataWidget(eGameBoard& b, eMainWindow* const w) :
    eWidget(w), mBoard(b) {}

void eDataWidget::initialize() {
    int h = 0;
    for(const auto b : mButtons) {
        addWidget(b);
        b->align(eAlignment::hcenter);
        h += b->height();
    }

    const auto res = resolution();
    const int m = res.multiplier();
    const auto space = new eWidget(window());
    space->setPadding(3*m);
    space->fitContent();
    addWidget(space);

    mInnerWidget = new eFramedWidget(window());
    mInnerWidget->setType(eFrameType::inner);
    mInnerWidget->setHeight(height() - h + 3*m);
    mInnerWidget->setWidth(width());
    mInnerWidget->setTinyPadding();
    addWidget(mInnerWidget);

    stackVertically();
    setNoPadding();
    fitContent();
}

void eDataWidget::setGameWidget(eGameWidget* const gw) {
    for(const auto b : mButtons) {
        b->setGameWidget(gw);
    }
}

void eDataWidget::addViewButton(eViewModeButton* const b) {
    mButtons.push_back(b);
}
