#include "eappealdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"

#include "elanguage.h"

void eAppealDataWidget::initialize() {
    mSeeAppeal = new eViewModeButton(
                     eLanguage::text("see_appeal"),
                     eViewMode::appeal,
                     window());
    addViewButton(mSeeAppeal);

    eDataWidget::initialize();
}
