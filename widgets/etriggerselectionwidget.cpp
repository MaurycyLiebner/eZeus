#include "etriggerselectionwidget.h"

#include "ebuttonslistwidget.h"

void eTriggerSelectionWidget::initialize(
        const eLabels& labels,
        const eTriggerAct& act) {
    setType(eFrameType::message);

    const auto blw = new eButtonsListWidget(window());
    const int p = padding();
    blw->resize(width() - 4*p, height() - 4*p);
    blw->initialize(false, false);
    blw->move(2*p, 2*p);
    addWidget(blw);

    blw->setButtonPressEvent(act);

    for(const auto& l : labels) {
        blw->addButton(l);
    }
}
