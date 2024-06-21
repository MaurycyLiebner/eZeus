#include "erockmissile.h"

#include "textures/egametextures.h"

eRockMissile::eRockMissile(eGameBoard& board,
                           const std::vector<ePathPoint>& path) :
    eMissile(board, eMissileType::rock, path) {
    eGameTextures::loadRock();
}

std::shared_ptr<eTexture> eRockMissile::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& rockTex = textures[id].fRock;
    return rockTex.getTexture(0);
}
