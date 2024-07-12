#include "erivalarmyawayeventwidget.h"

#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "widgets/ecitybutton.h"
#include "elanguage.h"

#include "widgets/egodbutton.h"

#include "gameEvents/erivalarmyawayevent.h"

void eRivalArmyAwayEventWidget::initialize(eRivalArmyAwayEvent* const e) {
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
