#include "eframedwidget.h"

#include "textures/egametextures.h"

void eFramedWidget::sizeHint(int& w, int& h) {
    const int p = padding();
    sizeHint2(w, h);
    int iRes;
    int dim;
    iResAndDim(iRes, dim);
    h = dim*int(std::ceil((2.*p + h)/dim)) - 2*p;
    w = dim*int(std::ceil((2.*p + w)/dim)) - 2*p;
}

void eFramedWidget::setType(const eFrameType type) {
    mType = type;
}

void eFramedWidget::paintEvent(ePainter& p) {
    int iRes;
    int dim;
    iResAndDim(iRes, dim);
    const auto& intrfc = eGameTextures::interface()[iRes];

    const int iMax = width()/dim;
    const int jMax = height()/dim;

    if(mType == eFrameType::outer){
        const auto& texs = intrfc.fComboBox[1];

        for(int i = 0; i < iMax; i++) {
            const int x = dim*i;
            for(int j = 0; j < jMax; j++) {
                const int y = dim*j;
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
                const auto& tex = texs.getTexture(texId);
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
            const int x = dim*i;
            for(int j = 0; j < jMax; j++) {
                const int y = dim*j;
                int collId;
                if(i == 0) {
                    if(j == 0) {
                        collId = 0;
                    } else if(j == jMax - 1) {
                        collId = 6;
                    } else {
                        collId = 3;
                    }
                } else if(i == iMax - 1) {
                    if(j == 0) {
                        collId = 2;
                    } else if(j == jMax - 1) {
                        collId = 8;
                    } else {
                        collId = 5;
                    }
                } else if(j == 0) {
                    collId = 1;
                } else if(j == jMax - 1) {
                    collId = 7;
                } else {
                    collId = 4;
                }
                const auto& coll = (*colls)[collId];
                const int texId = (i*j) % coll.size();
                const auto& tex = coll.getTexture(texId);
                p.drawTexture(x, y, tex);
            }
        }
    }
    p.drawRect(rect(), {0, 0, 0, 255}, 2);
}

void eFramedWidget::iResAndDim(int& iRes, int& dim) const {
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    iRes = static_cast<int>(uiScale);
    const int mult = iRes + 1;
    dim = 8*mult;
}
