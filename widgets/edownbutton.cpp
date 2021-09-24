#include "edownbutton.h"

#include "textures/egametextures.h"

eDownButton::eDownButton(eMainWindow* const window) :
    eButton(window) {

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& texs = intrfc[iRes];

    setPadding(0);
    setTexture(texs.fDownButton.getTexture(0));
    setHoverTexture(texs.fDownButton.getTexture(1));
    setPressedTexture(texs.fDownButton.getTexture(2));
    fitContent();
}
