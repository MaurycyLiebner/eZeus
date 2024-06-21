#include "earrowmissile.h"

#include "textures/egametextures.h"

eArrowMissile::eArrowMissile(eGameBoard& board,
                             const std::vector<ePathPoint>& path) :
    eMissile(board, eMissileType::arrow, path) {
    eGameTextures::loadArrow();
}

std::shared_ptr<eTexture>
eArrowMissile::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& rockTex = textures[id].fArrow;
    const double a = angle();
    const auto o = sAngleOrientation(a);
    const int texId = static_cast<int>(o);
    return rockTex.getTexture(texId);
}
