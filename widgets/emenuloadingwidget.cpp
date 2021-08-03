#include "emenuloadingwidget.h"

#include "textures/egametextures.h"

eMenuLoadingWidget::eMenuLoadingWidget(eMainWindow* const window) :
    eLoadingWidget(eGameTextures::menuSize(), [](std::string& text) {
        return eGameTextures::loadNextMenu(text);
    }, window) {}
