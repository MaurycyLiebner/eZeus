#include "emainmenubase.h"

#include "textures/egametextures.h"

void eMainMenuBase::initialize() {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    int iRes;
    switch(res) {
    case eRes::p2160:
    case eRes::p1440:
    case eRes::p1080:
        iRes = 2;
        break;
    case eRes::p720:
        iRes = 1;
        break;
    case eRes::p480:
        iRes = 0;
        break;
    }
    const auto& texs = intrfc[iRes];
    setTexture(texs.fMainMenuImage);
}
