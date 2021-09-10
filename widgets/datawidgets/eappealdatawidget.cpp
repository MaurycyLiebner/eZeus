#include "eappealdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"

void eAppealDataWidget::initialize() {
    mSeeAppeal = new eViewModeButton(
                     "See Appeal",
                     eViewMode::appeal,
                     window());

    addWidget(mSeeAppeal);
    mSeeAppeal->align(eAlignment::hcenter);
}

void eAppealDataWidget::setGameWidget(eGameWidget* const gw) {
    mSeeAppeal->setGameWidget(gw);
}
