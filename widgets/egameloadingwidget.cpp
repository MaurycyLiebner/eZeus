#include "egameloadingwidget.h"

#include "textures/egametextures.h"
#include "emusic.h"
#include "esounds.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::gameSize() + 2,
                   [](std::string& text) {
        const bool r = eGameTextures::loadNextGame(text);
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
