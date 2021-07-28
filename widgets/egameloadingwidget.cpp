#include "egameloadingwidget.h"

#include "eprogressbar.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eWidget(window) {}

void eGameLoadingWidget::initialize() {
    const auto pb = new eProgressBar(window());
    addWidget(pb);
    pb->align(eAlignment::center);
}

void eGameLoadingWidget::setDoneAction(const eAction& a) {
    mDoneAction = a;
}
