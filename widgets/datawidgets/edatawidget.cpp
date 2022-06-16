#include "edatawidget.h"

#include "eviewmodebutton.h"

void eDataWidget::initialize() {
    int h = 0;
    for(const auto b : mButtons) {
        addWidget(b);
        b->align(eAlignment::hcenter);
        h += b->height();
    }

    const auto space = new eWidget(window());
    space->setTinyPadding();
    space->fitContent();
    addWidget(space);

    mInnerWidget = new eFramedWidget(window());
    mInnerWidget->setType(eFrameType::inner);
    mInnerWidget->setHeight(height() - h);
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
