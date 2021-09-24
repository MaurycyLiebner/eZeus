#include "emainmenubase.h"

#include "textures/egametextures.h"

void eMainMenuBase::initialize() {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    setTexture(texs.fMainMenuImage);
}
