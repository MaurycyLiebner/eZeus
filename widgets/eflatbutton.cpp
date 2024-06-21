#include "eflatbutton.h"

#include "textures/egametextures.h"

void eFlatButton::paintEvent(ePainter& p) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);
    const int dim = 8*mult;
    const auto& intrfc = eGameTextures::interface()[iRes];
    if(!intrfc.fLoaded) return;

    const int iMax = width()/dim + 1;
    const int lastX = width() - dim;

    const eTextureCollection& coll =
            hovered() ? intrfc.fBuildingButtonHover :
                        intrfc.fBuildingButton;

    for(int i = 0; i < iMax; i++) {
        const int x = i == iMax - 1 ? lastX : dim*i;
        stdsptr<eTexture> tex;
        if(i == 0) {
            tex = coll.getTexture(0);
        } else if(i == iMax - 1) {
            tex = coll.getTexture(2);
        } else {
            tex = coll.getTexture(1);
        }
        p.drawTexture(x, 0, tex);
    }

    eButtonBase::paintEvent(p);
}
