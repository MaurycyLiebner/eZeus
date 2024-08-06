#include "ebasiccityeventwidget.h"

#include "widgets/elabeledwidget.h"
#include "widgets/ecitybutton.h"
#include "elanguage.h"

#include "gameEvents/ebasiccityevent.h"

void eBasicCityEventWidget::initialize(eBasicCityEvent* const e) {
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

    const int p = padding();
    stackVertically(p);
    fitContent();
}
