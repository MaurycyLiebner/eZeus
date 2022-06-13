#include "emenuloadingwidget.h"

#include "textures/egametextures.h"
#include "emusic.h"
#include "esounds.h"
#include "emessages.h"
#include "elanguage.h"
#include "emainwindow.h"

eMenuLoadingWidget::eMenuLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::menuSize(),
                   [window](std::string& text) {
    const auto& sett = window->settings();
        const bool r = eGameTextures::loadNextMenu(sett, text);
        if(r) {
            text = "Loading music...";
            eMusic::loadMenu();
            eSounds::loadButtonSound();
            eLanguage::load();
            return true;
        }
        return false;
    }, window, false) {}
