#include "erockmissile.h"

#include "textures/egametextures.h"

std::shared_ptr<eTexture> eRockMissile::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& rockTex = textures[id].fRock;
    return rockTex.getTexture(0);
}
