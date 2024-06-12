#include "ereceiverequesteventwidget.h"

#include "widgets/eresourcebutton.h"
#include "widgets/ecitybutton.h"
#include "widgets/evaluebutton.h"
#include "widgets/elabeledwidget.h"
#include "elanguage.h"

void eReceiveRequestEventWidget::initialize(eReceiveRequestEvent* const e) {
    const auto cityButtonL = new eLabeledWidget(window());
    const auto cityButton = new eCityButton(window());
    const auto board = e->worldBoard();
    cityButton->initialize(board, [e](const stdsptr<eWorldCity>& c){
        e->setCity(c);
    });
    const auto cc = e->city();
    cityButton->setCity(cc);
    cityButtonL->setup(eLanguage::text("city:"), cityButton);
    addWidget(cityButtonL);

    const auto resourceL = new eLabeledWidget(window());

    const auto resourceCountButton = new eValueButton(window());
    resourceCountButton->setValueChangeAction([e](const int p) {
        e->setResourceCount(p);
    });
    resourceCountButton->initialize(1, 999);
    const int rc = e->resourceCount();
    resourceCountButton->setValue(rc);

    const auto resourceTypeButton = new eResourceButton(window());
    resourceTypeButton->initialize([e](const eResourceType r){
        e->setResourceType(r);
    });
    const auto rr = e->resourceType();
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
