#include "egamemainmenu.h"

#include "ebutton.h"

#include "elanguage.h"

void eGameMainMenu::initialize(const eAction& exitAct) {
    const auto exitButt = new eButton(window());
    exitButt->setText(eLanguage::text("exit"));
    exitButt->fitContent();
    exitButt->setPressAction(exitAct);
    addWidget(exitButt);
    exitButt->align(eAlignment::hcenter);
    layoutVertically();
}
