#include "emainmenubase.h"

#include "textures/egametextures.h"

void eMainMenuBase::initialize() {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    int iRes;
    switch(res.uiScale()) {
    case eUIScale::large:
        iRes = 2;
        break;
    case eUIScale::medium:
        iRes = 1;
        break;
    case eUIScale::small:
        iRes = 0;
        break;
    }
    const auto& texs = intrfc[iRes];
    setTexture(texs.fMainMenuImage);
}
