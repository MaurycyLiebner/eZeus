#include "egyminfowidget.h"

#include "../ebutton.h"

eGymInfoWidget::eGymInfoWidget(eMainWindow* const window) :
    eInfoWidget(window) {

}

void eGymInfoWidget::initialize(const eAction& closeAction) {
    eInfoWidget::initialize();
    const auto ok = new eButton(window());
    ok->setText("OK");
    ok->fitContent();
    ok->setPressAction(closeAction);

    addWidget(ok);
    ok->align(eAlignment::bottom | eAlignment::right);
}
