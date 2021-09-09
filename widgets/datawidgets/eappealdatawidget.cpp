#include "eappealdatawidget.h"

#include "../echeckablebutton.h"

#include "widgets/egamewidget.h"

void eAppealDataWidget::initialize() {
    mSeeAppeal = new eCheckableButton(window());
    mSeeAppeal->setCheckAction([this](const bool) {
        if(!mGW) return;
        const auto vm = mGW->viewMode();
        if(vm == eViewMode::appeal) {
            mGW->setViewMode(eViewMode::defaultView);
        } else {
            mGW->setViewMode(eViewMode::appeal);
        }
    });
    mSeeAppeal->setSmallFontSize();
    mSeeAppeal->setPadding(mSeeAppeal->padding()/2);
    mSeeAppeal->setText("See Appeal");
    mSeeAppeal->fitContent();

    addWidget(mSeeAppeal);
    mSeeAppeal->align(eAlignment::hcenter);
}

void eAppealDataWidget::setGameWidget(eGameWidget* const gw) {
    mGW = gw;
}

void eAppealDataWidget::paintEvent(ePainter& p) {
    if(mGW) {
        const auto vm = mGW->viewMode();
        mSeeAppeal->setChecked(vm == eViewMode::appeal);
    }
    eWidget::paintEvent(p);
}
