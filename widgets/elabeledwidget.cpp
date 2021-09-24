#include "elabeledwidget.h"

eLabeledWidget::eLabeledWidget(eMainWindow* const window) :
    eWidget(window) {
    setNoPadding();
}

void eLabeledWidget::setup(const std::string& label, eWidget* const w) {
    const auto l = new eLabel(label, window());
    l->fitContent();

    addWidget(l);
    addWidget(w);

    fitContent();

    const int margin = resolution().margin();
    setWidth(3*margin + l->width() + w->width());

    l->align(eAlignment::vcenter);
    w->align(eAlignment::vcenter);

    layoutHorizontally();
}
