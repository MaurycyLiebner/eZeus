#include "egameloadingwidget.h"

#include "textures/egametextures.h"
#include "emusic.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::gameSize(), [](std::string& text) {
        const bool r = eGameTextures::loadNextGame(text);
        if(r) {
            text = "Loading music...";
            eMusic::load();
            return true;
        }
        return false;
    }, window) {}
