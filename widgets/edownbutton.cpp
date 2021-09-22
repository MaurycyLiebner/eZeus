#include "edownbutton.h"

#include "textures/egametextures.h"

eDownButton::eDownButton(eMainWindow* const window) :
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
    setTexture(texs.fDownButton.getTexture(0));
    setHoverTexture(texs.fDownButton.getTexture(1));
    setPressedTexture(texs.fDownButton.getTexture(2));
    fitContent();
}
