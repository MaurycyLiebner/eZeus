#include "egameloadingwidget.h"

#include "textures/egametextures.h"
#include "emusic.h"
#include "esounds.h"
#include "emainwindow.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::gameSize(window->settings()) + 2,
                   [window](std::string& text) {
        const auto& sett = window->settings();
        const bool r = eGameTextures::loadNextGame(sett, text);
        if(r) {
            const bool r = eMusic::loaded();
            if(r) {
                const bool r = eSounds::loaded();
                if(r) return true;
                text = "Loading sounds...";
                eSounds::load();
                return false;
            } else {
                text = "Loading music...";
                eMusic::load();
                return false;
            }
        }
        return false;
    }, window) {}
