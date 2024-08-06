#include "epricechangeeventwidget.h"

#include "widgets/eresourcebutton.h"
#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "elanguage.h"

#include "gameEvents/epricechangeevent.h"

void ePriceChangeEventWidget::initialize(
        ePriceChangeEvent* const e) {
    const auto resourceL = new eLabeledWidget(window());

    const auto resourceCountButton = new eValueButton(window());
    resourceCountButton->setValueChangeAction([e](const int p) {
        e->setBy(p);
    });
    resourceCountButton->initialize(-999, 999);
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
