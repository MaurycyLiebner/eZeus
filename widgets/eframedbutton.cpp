#include "eframedbutton.h"

#include "textures/egametextures.h"

void eFramedButton::paintEvent(ePainter& p) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);
    const int dim = 8*mult;
    const auto& intrfc = eGameTextures::interface()[iRes];
    if(!intrfc.fLoaded) return;

    const eTextureCollection* coll = nullptr;
    if(hovered()) {
        coll = &intrfc.fButtonFrameHover;
    } else {
        coll = &intrfc.fButtonFrame;
    }

    const int iMax = width()/dim + 1;
    const int jMax = height()/dim + 1;

    const int lastX = width() - dim;
    const int lastY = height() - dim;

    const auto texCollId = [&](const int i, const int j) {
        int texId;
        if(i == 0) {
            if(j == 0) {
                texId = 0;
            } else if(j == jMax - 1) {
                texId = 6;
            } else {
                texId = 7;
            }
        } else if(i == iMax - 1) {
            if(j == 0) {
                texId = 2;
            } else if(j == jMax - 1) {
                texId = 4;
            } else {
                texId = 3;
            }
        } else if(j == 0) {
            texId = 1;
        } else if(j == jMax - 1) {
            texId = 5;
        } else {
            texId = -1;
        }
        return texId;
    };

    for(int i = 0; i < iMax; i++) {
        const int x = i == iMax - 1 ? lastX : dim*i;
        for(int j = 0; j < jMax; j++) {
            const int texId = texCollId(i, j);
            if(texId == -1) continue;
            const auto& tex = coll->getTexture(texId);
            const int y = j == jMax - 1 ? lastY : dim*j;
            p.drawTexture(x, y, tex);
        }
    }
    eButton::paintEvent(p);
}
