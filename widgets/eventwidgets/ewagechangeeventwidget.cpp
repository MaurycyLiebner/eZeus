#include "ewagechangeeventwidget.h"

#include "widgets/eresourcebutton.h"
#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "elanguage.h"

#include "gameEvents/ewagechangeevent.h"

void eWageChangeEventWidget::initialize(
        eWageChangeEvent* const e) {
    const auto percentL = new eLabeledWidget(window());

    const auto percent = new eValueButton(window());
    percent->setValueChangeAction([e](const int p) {
        e->setBy(p);
    });
    percent->initialize(-99, 999);
    const int rc = e->by();
    percent->setValue(rc);

    percentL->setup(eLanguage::text("percent:"), percent);
    addWidget(percentL);

    const int p = padding();
    stackVertically(p);
    fitContent();
}
