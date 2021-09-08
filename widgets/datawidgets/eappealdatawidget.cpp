#include "eappealdatawidget.h"

#include "../ebutton.h"

#include "widgets/egamewidget.h"

void eAppealDataWidget::initialize() {
    const auto button = new eButton(window());
    button->setPressAction([this]() {
        if(!mGW) return;
        const auto vm = mGW->viewMode();
        if(vm == eViewMode::appeal) {
            mGW->setViewMode(eViewMode::defaultView);
        } else {
            mGW->setViewMode(eViewMode::appeal);
        }
    });
    button->setSmallFontSize();
    button->setText("Appeal");
    button->fitContent();

    addWidget(button);
    button->align(eAlignment::hcenter);
}

void eAppealDataWidget::setGameWidget(eGameWidget* const gw) {
    mGW = gw;
}
