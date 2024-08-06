#include "esupplydemandchangeeventwidget.h"

#include "widgets/eresourcebutton.h"
#include "widgets/elabeledwidget.h"
#include "widgets/ecitybutton.h"
#include "widgets/evaluebutton.h"
#include "elanguage.h"

#include "gameEvents/esupplydemandchangeevent.h"

void eSupplyDemandChangeEventWidget::initialize(
        eSupplyDemandChangeEvent* const e) {
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

    const auto resourceL = new eLabeledWidget(window());

    const auto resourceCountButton = new eValueButton(window());
    resourceCountButton->setValueChangeAction([e](const int p) {
        e->setBy(p);
    });
    resourceCountButton->initialize(-99, 99);
    const int rc = e->by();
    resourceCountButton->setValue(rc);

    const auto resourceTypeButton = new eResourceButton(window());
    resourceTypeButton->initialize([e](const eResourceType r){
        e->setType(r);
    });
    const auto rr = e->type();
    resourceTypeButton->setResource(rr);

    const auto resource = new eWidget(window());
    resource->setNoPadding();
    resource->addWidget(resourceCountButton);
    resource->addWidget(resourceTypeButton);
    const int p = padding();
    resource->stackHorizontally(p);
    resource->fitContent();
    resourceL->setup(eLanguage::text("resource:"), resource);
    addWidget(resourceL);

    stackVertically(p);
    fitContent();
}
