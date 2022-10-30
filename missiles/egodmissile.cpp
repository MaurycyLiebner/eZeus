#include "egodmissile.h"

std::shared_ptr<eTexture>
eGodMissile::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& coll = textures[id].*mTex;
    const double a = angle();
    const auto o = sAngleOrientation(a);
    const int texId = static_cast<int>(o) + 8*textureTime();
    return coll.getTexture(texId % coll.size());
}

void eGodMissile::setTexture(const eTexPtr tex) {
    mTex = tex;
}
