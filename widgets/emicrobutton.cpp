#include "emicrobutton.h"

#include "textures/egametextures.h"

void eMicroButton::sizeHint(int& w, int& h) {
    eButtonBase::sizeHint(w, h);
    const auto res = resolution();
    const double mult = res.multiplier();
    h = std::round(13*mult);
}

void eMicroButton::paintEvent(ePainter& p) {
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const double mult = res.multiplier();
    const int wdim = std::round(18*mult);
    const auto& intrfc = eGameTextures::interface()[iRes];
    if(!intrfc.fLoaded) return;

    const int iMax = width()/wdim + 1;
    const int lastX = width() - wdim;

    const bool h = hovered();
    const bool pp = pressed();
    const bool e = enabled();
    int texId;
    if(!e) texId = 3;
    else if(pp) texId = 2;
    else if(h) texId = 1;
    else texId = 0;

    for(int i = 0; i < iMax; i++) {
        const int x = i == iMax - 1 ? lastX : wdim*i;
        const eTextureCollection* coll;
        if(i == 0) {
            coll = &intrfc.fMicroButton[0];
        } else if(i == iMax - 1) {
            coll = &intrfc.fMicroButton[2];
        } else {
            coll = &intrfc.fMicroButton[1];
        }
        const auto& tex = coll->getTexture(texId);
        p.drawTexture(x, 0, tex);
    }

    eButtonBase::paintEvent(p);
}
