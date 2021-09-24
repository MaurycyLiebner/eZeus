#include "echeckbox.h"

#include "textures/egametextures.h"

eCheckBox::eCheckBox(eMainWindow* const window) :
    eCheckableButton(window) {
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& intrfc = eGameTextures::interface();
    const auto& texs = intrfc[iRes].fCheckBox;
    setCheckedTexture(texs.getTexture(0));
    setTexture(texs.getTexture(1));
    setPadding(0);
    fitContent();
}
