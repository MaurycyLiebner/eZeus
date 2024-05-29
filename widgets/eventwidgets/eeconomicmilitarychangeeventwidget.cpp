#include "eeconomicmilitarychangeeventwidget.h"

#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "widgets/ecitybutton.h"
#include "elanguage.h"

#include "gameEvents/eeconomicmilitarychangeeventbase.h"

void eEconomicMilitaryChangeEventWidget::initialize(eEconomicMilitaryChangeEventBase* const e) {
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

    const auto byButtonL = new eLabeledWidget(window());
    const auto byButton = new eValueButton(window());
    byButton->setValueChangeAction([e](const int by) {
        e->setBy(by);
    });
    byButton->initialize(-5, 5);
    byButton->setValue(e->by());
    byButtonL->setup(eLanguage::text("change_by:"), byButton);
    addWidget(byButtonL);

    const int p = padding();
    stackVertically(p);
    fitContent();
}
