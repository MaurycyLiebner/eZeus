#include "echeckbox.h"

#include "textures/egametextures.h"

eCheckBox::eCheckBox(eMainWindow* const window) :
    eCheckableButton(window) {
    int iRes;
    const auto res = resolution();
    switch(res) {
    case eRes::p2160:
    case eRes::p1440:
        iRes = 2;
        break;
    case eRes::p1080:
    case eRes::p720:
        iRes = 1;
        break;
    case eRes::p480:
        iRes = 0;
        break;
    }
    const auto& intrfc = eGameTextures::interface();
    const auto& texs = intrfc[iRes].fCheckBox;
    setCheckedTexture(texs.getTexture(0));
    setTexture(texs.getTexture(1));
    setPadding(0);
    fitContent();
}
