#include "egamemainmenu.h"

#include "eframedbutton.h"

#include "elanguage.h"

#include "engine/egameboard.h"
#include "fileIO/ewritestream.h"

void eGameMainMenu::initialize(const eAction& resumeAct,
                               const eAction& saveAct,
                               const eAction& loadAct,
                               const eAction& exitAct) {
    setType(eFrameType::message);

    const auto resButt = new eFramedButton(window());
    resButt->setUnderline(false);
    resButt->setText(eLanguage::text("resume_game"));
    resButt->fitContent();
    resButt->setPressAction(resumeAct);
    addWidget(resButt);
    resButt->align(eAlignment::hcenter);

    const auto saveButt = new eFramedButton(window());
    saveButt->setUnderline(false);
    saveButt->setText(eLanguage::zeusText(1, 4));
    saveButt->fitContent();
    saveButt->setPressAction(saveAct);
    addWidget(saveButt);
    saveButt->align(eAlignment::hcenter);

    const auto loadButt = new eFramedButton(window());
    loadButt->setUnderline(false);
    loadButt->setText(eLanguage::zeusText(1, 3));
    loadButt->fitContent();
    loadButt->setPressAction(loadAct);
    addWidget(loadButt);
    loadButt->align(eAlignment::hcenter);

    const auto exitButt = new eFramedButton(window());
    exitButt->setUnderline(false);
    exitButt->setText(eLanguage::zeusText(1, 5));
    exitButt->fitContent();
    exitButt->setPressAction(exitAct);
    addWidget(exitButt);
    exitButt->align(eAlignment::hcenter);

    layoutVertically();
}
