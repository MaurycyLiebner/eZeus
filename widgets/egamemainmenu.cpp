#include "egamemainmenu.h"

#include "ebutton.h"

void eGameMainMenu::initialize(const eAction& exitAct) {
    const auto exitButt = new eButton(window());
    exitButt->setText("Exit");
    exitButt->fitContent();
    exitButt->setPressAction(exitAct);
    addWidget(exitButt);
    exitButt->align(eAlignment::hcenter);
    layoutVertically();
}
