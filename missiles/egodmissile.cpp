#include "egodmissile.h"

std::shared_ptr<eTexture>
eGodMissile::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& coll = textures[id].*mTex;
    const double a = angle();
    const double inc = 360./8.;
    const double aa = a + 90;
    const double aaa = aa > 360. ? aa - 360. : aa;
    const int texId = std::floor(aaa/inc) + 8*textureTime();
    return coll.getTexture(texId % coll.size());
}

void eGodMissile::setTexture(const eTexPtr tex) {
    mTex = tex;
}
