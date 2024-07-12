#include "eeartquakeeventwidget.h"

#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "elanguage.h"

#include "widgets/egodbutton.h"

#include "gameEvents/eearthquakeevent.h"

void eEartquakeEventWidget::initialize(eEarthquakeEvent* const e) {
    const auto godButtonL = new eLabeledWidget(window());
    const auto act = [e](const eGodType type) {
        e->setGod(type);
    };
    const auto godButton = new eGodButton(window());
    godButton->initialize(act);
    const auto iniT = e->god();
    godButton->setType(iniT);
    godButtonL->setup(eLanguage::text("god:"), godButton);
    addWidget(godButtonL);

    const auto sizeButtonL = new eLabeledWidget(window());
    const auto sizeButton = new eValueButton(window());
    sizeButton->setValueChangeAction([e](const int s) {
        e->setSize(s);
    });
    sizeButton->initialize(0, 9999);
    sizeButton->setValue(e->size());
    sizeButtonL->setup(eLanguage::text("size:"), sizeButton);
    addWidget(sizeButtonL);

    const auto disasterPointButtonL = new eLabeledWidget(window());
    const auto disasterPointButton = new eValueButton(window());
    disasterPointButton->setValueChangeAction([e](const int p) {
        e->setDisasterPoint(p - 1);
    });
    disasterPointButton->initialize(0, 999);
    disasterPointButton->setValue(e->disasterPoint() + 1);
    disasterPointButtonL->setup(eLanguage::text("disaster_point:"), disasterPointButton);
    addWidget(disasterPointButtonL);

    const int p = padding();
    stackVertically(p);
    fitContent();
}
