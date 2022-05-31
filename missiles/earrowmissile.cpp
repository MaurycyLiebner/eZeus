#include "earrowmissile.h"

#include "textures/egametextures.h"

std::shared_ptr<eTexture>
eArrowMissile::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& rockTex = textures[id].fArrow;
    const double a = angle();
    const double inc = 360./32.;
    const double aa = a + 90 + 2*inc;
    const double aaa = aa > 360. ? aa - 360. : aa;
    return rockTex.getTexture(std::floor(aaa/inc));
}
