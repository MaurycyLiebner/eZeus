#include "eappealdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"

#include "elanguage.h"

void eAppealDataWidget::initialize() {
    mSeeAppeal = new eViewModeButton(
                     eLanguage::text("see_appeal"),
                     eViewMode::appeal,
                     window());

    addWidget(mSeeAppeal);
    mSeeAppeal->align(eAlignment::hcenter);
}

void eAppealDataWidget::setGameWidget(eGameWidget* const gw) {
    mSeeAppeal->setGameWidget(gw);
}
