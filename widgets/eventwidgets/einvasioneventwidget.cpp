#include "einvasioneventwidget.h"

#include "engine/egameboard.h"

#include "widgets/eframedbutton.h"
#include "widgets/echoosebutton.h"
#include "elanguage.h"
#include "emainwindow.h"
#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "widgets/ecitybutton.h"

void eInvasionEventWidget::initialize(eInvasionEvent* const e) {
    const auto cityButtonL = new eLabeledWidget(window());
    const auto cc = e->city();
    const auto cityButton = new eCityButton(window());
    auto& board = e->getBoard();
    cityButton->initialize(board, [e](const stdsptr<eWorldCity>& c){
        e->setCity(c);
    });
    cityButton->setCity(cc);
    cityButtonL->setup(eLanguage::text("city:"), cityButton);
    addWidget(cityButtonL);

    const auto infantryButtonL = new eLabeledWidget(window());
    const auto infantryButton = new eValueButton(window());
    infantryButton->setValueChangeAction([e](const int p) {
        e->setInfantry(p);
    });
    infantryButton->initialize(0, 999);
    infantryButton->setValue(e->infantry());
    infantryButtonL->setup(eLanguage::text("infantry:"), infantryButton);
    addWidget(infantryButtonL);

    const auto cavalryButtonL = new eLabeledWidget(window());
    const auto cavalryButton = new eValueButton(window());
    cavalryButton->setValueChangeAction([e](const int p) {
        e->setCavalry(p);
    });
    cavalryButton->initialize(0, 999);
    cavalryButton->setValue(e->cavalry());
    cavalryButtonL->setup(eLanguage::text("cavalry:"), cavalryButton);
    addWidget(cavalryButtonL);

    const auto archersButtonL = new eLabeledWidget(window());
    const auto archersButton = new eValueButton(window());
    archersButton->setValueChangeAction([e](const int p) {
        e->setArchers(p);
    });
    archersButton->initialize(0, 999);
    archersButton->setValue(e->archers());
    archersButtonL->setup(eLanguage::text("archers:"), archersButton);
    addWidget(archersButtonL);

    const int p = padding();
    stackVertically(p);
    fitContent();
}
