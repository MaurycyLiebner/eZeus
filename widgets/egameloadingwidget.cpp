#include "egameloadingwidget.h"

#include "textures/egametextures.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::gameSize(), [](std::string& text) {
        return eGameTextures::loadNextGame(text);
    }, window) {}
