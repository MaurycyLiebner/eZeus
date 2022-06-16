#include "emilitarydatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"

void eMilitaryDataWidget::initialize() {
    {
        mSeeSecurity = new eViewModeButton(
                        eLanguage::text("see_security"),
                        eViewMode::husbandry,
                        window());
        addViewButton(mSeeSecurity);
    }

    eDataWidget::initialize();
}
