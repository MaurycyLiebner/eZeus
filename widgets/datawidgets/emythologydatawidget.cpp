#include "emythologydatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eMythologyDataWidget::initialize() {
    {
        mSeeImmortals = new eViewModeButton(
                        eLanguage::text("see_immortals"),
                        eViewMode::immortals,
                        window());
        addViewButton(mSeeImmortals);
    }

    eDataWidget::initialize();
}
