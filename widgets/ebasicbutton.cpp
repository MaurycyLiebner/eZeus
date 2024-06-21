#include "ebasicbutton.h"

eBasicButton::eBasicButton(const eTex tex,
                           eMainWindow* const window) :
    eButton(window) {

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& texs = intrfc[iRes];

    setPadding(0);
    const auto& coll = (texs.*tex);
    setTexture(coll.getTexture(0));
    setHoverTexture(coll.getTexture(1));
    setPressedTexture(coll.getTexture(2));
    fitContent();
}
