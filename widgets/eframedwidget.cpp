#include "eframedwidget.h"

#include "textures/egametextures.h"

void eFramedWidget::setType(const eFrameType type) {
    mType = type;
}

void eFramedWidget::paintEvent(ePainter& p) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);
    const int dim = 8*mult;
    const auto& intrfc = eGameTextures::interface()[iRes];
    if(!intrfc.fLoaded) return;

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
                texId = 3;
            }
        } else if(i == iMax - 1) {
            if(j == 0) {
                texId = 2;
            } else if(j == jMax - 1) {
                texId = 8;
            } else {
                texId = 5;
            }
        } else if(j == 0) {
            texId = 1;
        } else if(j == jMax - 1) {
            texId = 7;
        } else {
            texId = 4;
        }
        return texId;
    };

    if(mType == eFrameType::outer){
        const auto& texs = intrfc.fComboBox[1];

        for(int i = 0; i < iMax; i++) {
            const int x = i == iMax - 1 ? lastX : dim*i;
            for(int j = 0; j < jMax; j++) {
                const int texId = texCollId(i, j);
                const auto& tex = texs.getTexture(texId);
                const int y = j == jMax - 1 ? lastY : dim*j;
                p.drawTexture(x, y, tex);
            }
        }
    } else {
        const std::vector<eTextureCollection>* colls = nullptr;
        if(mType == eFrameType::message) {
            colls = &intrfc.fMessageBox;
        } else {
            colls = &intrfc.fInnerBox;
        }

        for(int i = 0; i < iMax; i++) {
            const int x = i == iMax - 1 ? lastX : dim*i;
            for(int j = 0; j < jMax; j++) {
                const int collId = texCollId(i, j);
                const auto& coll = (*colls)[collId];
                const int texId = (i*j) % coll.size();
                const auto& tex = coll.getTexture(texId);
                const int y = j == jMax - 1 ? lastY : dim*j;
                p.drawTexture(x, y, tex);
            }
        }
    }
    p.drawRect(rect(), {0, 0, 0, 255}, 2);
}
