#include "echeckbox.h"

#include "textures/egametextures.h"

eCheckBox::eCheckBox(eMainWindow* const window) :
    eCheckableButton(window) {
    int iRes;
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    switch(uiScale) {
    case eUIScale::small:
        iRes = 0;
        break;
    case eUIScale::medium:
        iRes = 1;
        break;
    case eUIScale::large:
        iRes = 2;
        break;
    }
    const auto& intrfc = eGameTextures::interface();
    const auto& texs = intrfc[iRes].fCheckBox;
    setCheckedTexture(texs.getTexture(0));
    setTexture(texs.getTexture(1));
    setPadding(0);
    fitContent();
}
