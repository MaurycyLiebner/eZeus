#include "eappealdatawidget.h"

#include "../echeckablebutton.h"

#include "widgets/egamewidget.h"

void eAppealDataWidget::initialize() {
    const auto button = new eCheckableButton(window());
    button->setCheckAction([this](const bool) {
        if(!mGW) return;
        const auto vm = mGW->viewMode();
        if(vm == eViewMode::appeal) {
            mGW->setViewMode(eViewMode::defaultView);
        } else {
            mGW->setViewMode(eViewMode::appeal);
        }
    });
    button->setSmallFontSize();
    button->setPadding(button->padding()/2);
    button->setText("See Appeal");
    button->fitContent();

    addWidget(button);
    button->align(eAlignment::hcenter);
}

void eAppealDataWidget::setGameWidget(eGameWidget* const gw) {
    mGW = gw;
}
