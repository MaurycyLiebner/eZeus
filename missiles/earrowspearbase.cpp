#include "earrowspearbase.h"

eArrowSpearBase::eArrowSpearBase(eGameBoard& board,
                                 const eMissileTexs missileTexs,
                                 const eMissileType type,
                                 const std::vector<ePathPoint>& path) :
    eMissile(board, type, path),
    mTexs(missileTexs) {}

std::shared_ptr<eTexture>
eArrowSpearBase::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& rockTex = textures[id].*mTexs;
    const double a = angle();
    const int iid = std::round(((a - 225)/11.25));
    const int texId = iid < 0 ? ((32 + iid) % 32) :
                                (iid % 32);
    return rockTex.getTexture(texId);
}
