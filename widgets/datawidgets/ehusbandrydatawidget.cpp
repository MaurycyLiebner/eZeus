#include "ehusbandrydatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eHusbandryDataWidget::initialize() {
    {
        mSeeHusbandry = new eViewModeButton(
                        eLanguage::text("see_husbandry"),
                        eViewMode::husbandry,
                        window());
        addViewButton(mSeeHusbandry);
    }

    eDataWidget::initialize();
}
