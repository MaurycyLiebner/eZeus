#include "egamemainmenu.h"

#include "ebutton.h"

#include "elanguage.h"

#include "engine/egameboard.h"
#include "fileIO/ewritestream.h"

void eGameMainMenu::initialize(const eAction& saveAct,
                               const eAction& loadAct,
                               const eAction& exitAct) {
    setType(eFrameType::message);

    const auto saveButt = new eButton(window());
    saveButt->setText(eLanguage::text("save_game"));
    saveButt->fitContent();
    saveButt->setPressAction(saveAct);
    addWidget(saveButt);
    saveButt->align(eAlignment::hcenter);

    const auto loadButt = new eButton(window());
    loadButt->setText(eLanguage::text("load_game"));
    loadButt->fitContent();
    loadButt->setPressAction(loadAct);
    addWidget(loadButt);
    loadButt->align(eAlignment::hcenter);

    const auto exitButt = new eButton(window());
    exitButt->setText(eLanguage::text("exit"));
    exitButt->fitContent();
    exitButt->setPressAction(exitAct);
    addWidget(exitButt);
    exitButt->align(eAlignment::hcenter);

    layoutVertically();
}
