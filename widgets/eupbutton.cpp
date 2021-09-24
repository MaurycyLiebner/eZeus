#include "eupbutton.h"

#include "textures/egametextures.h"

eUpButton::eUpButton(eMainWindow* const window) :
    eButton(window) {

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& texs = intrfc[iRes];

    setPadding(0);
    setTexture(texs.fUpButton.getTexture(0));
    setHoverTexture(texs.fUpButton.getTexture(1));
    setPressedTexture(texs.fUpButton.getTexture(2));
    fitContent();
}
