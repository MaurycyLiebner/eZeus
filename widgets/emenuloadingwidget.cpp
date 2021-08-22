#include "emenuloadingwidget.h"

#include "textures/egametextures.h"
#include "emusic.h"

eMenuLoadingWidget::eMenuLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::menuSize(), [](std::string& text) {
        const bool r = eGameTextures::loadNextMenu(text);
        if(r) {
            text = "Loading music...";
            eMusic::loadMenu();
            return true;
        }
        return false;
    }, window, false) {}
