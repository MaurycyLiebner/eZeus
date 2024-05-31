#include "etroopsrequesteventwidget.h"

#include "widgets/eresourcebutton.h"
#include "widgets/ecitybutton.h"
#include "widgets/evaluebutton.h"
#include "widgets/elabeledwidget.h"
#include "elanguage.h"

void eTroopsRequestEventWidget::initialize(eTroopsRequestEvent* const e) {
    const auto cityButtonL = new eLabeledWidget(window());
    const auto cityButton = new eCityButton(window());
    auto& board = e->getBoard();
    cityButton->initialize(board, [e](const stdsptr<eWorldCity>& c){
        e->setCity(c);
    });
    const auto cc = e->city();
    cityButton->setCity(cc);
    cityButtonL->setup(eLanguage::text("city:"), cityButton);
    addWidget(cityButtonL);

    const auto rivalButtonL = new eLabeledWidget(window());
    const auto rivalButton = new eCityButton(window());
    rivalButton->initialize(board, [e](const stdsptr<eWorldCity>& c){
        e->setRivalCity(c);
    });
    const auto rival = e->rivalCity();
    rivalButton->setCity(cc);
    rivalButtonL->setup(eLanguage::text("rival:"), rivalButton);
    addWidget(rivalButtonL);

    const int p = padding();

    stackVertically(p);
    fitContent();
}
