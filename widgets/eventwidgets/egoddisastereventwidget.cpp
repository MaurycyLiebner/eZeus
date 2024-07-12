#include "egoddisastereventwidget.h"

#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "widgets/ecitybutton.h"
#include "elanguage.h"

#include "widgets/egodbutton.h"

#include "gameEvents/egoddisasterevent.h"

void eGodDisasterEventWidget::initialize(eGodDisasterEvent* const e) {
    const auto cityButtonL = new eLabeledWidget(window());
    const auto cc = e->city();
    const auto cityButton = new eCityButton(window());
    const auto board = e->worldBoard();
    cityButton->initialize(board, [e](const stdsptr<eWorldCity>& c){
        e->setCity(c);
    });
    cityButton->setCity(cc);
    cityButtonL->setup(eLanguage::text("city:"), cityButton);
    addWidget(cityButtonL);

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

    const auto durButtonL = new eLabeledWidget(window());
    const auto durButton = new eValueButton(window());
    durButton->setValueChangeAction([e](const int d) {
        e->setDuration(d);
    });
    durButton->initialize(0, 9999);
    durButton->setValue(e->duration());
    durButtonL->setup(eLanguage::text("duration:"), durButton);
    addWidget(durButtonL);

    const int p = padding();
    stackVertically(p);
    fitContent();
}
