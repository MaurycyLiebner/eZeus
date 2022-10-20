#include "egamemainmenu.h"

#include "ebutton.h"

#include "elanguage.h"

#include "engine/egameboard.h"
#include "fileIO/ewritestream.h"

void eGameMainMenu::initialize(const eAction& exitAct,
                               eGameBoard* const board) {
    const auto saveAct = [board]() {
        const std::string basedir{"../saves/"};
        const auto path = basedir + "1.ez";
        const auto file = SDL_RWFromFile(path.c_str(), "w+b");
        if(!file) return;
        eWriteStream dst(file);
        board->write(dst);
        SDL_RWclose(file);
    };

    const auto saveButt = new eButton(window());
    saveButt->setText(eLanguage::text("save"));
    saveButt->fitContent();
    saveButt->setPressAction(saveAct);
    addWidget(saveButt);
    saveButt->align(eAlignment::hcenter);

    const auto exitButt = new eButton(window());
    exitButt->setText(eLanguage::text("exit"));
    exitButt->fitContent();
    exitButt->setPressAction(exitAct);
    addWidget(exitButt);
    exitButt->align(eAlignment::hcenter);

    layoutVertically();
}
