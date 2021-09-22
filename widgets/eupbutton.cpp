#include "eupbutton.h"

#include "textures/egametextures.h"

eUpButton::eUpButton(eMainWindow* const window) :
    eButton(window) {

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    int iRes;
    switch(res.uiScale()) {
    case eUIScale::large:
        iRes = 2;
        break;
    case eUIScale::medium:
        iRes = 1;
        break;
    case eUIScale::small:
        iRes = 0;
        break;
    }
    const auto& texs = intrfc[iRes];

    setPadding(0);
    setTexture(texs.fUpButton.getTexture(0));
    setHoverTexture(texs.fUpButton.getTexture(1));
    setPressedTexture(texs.fUpButton.getTexture(2));
    fitContent();
}
