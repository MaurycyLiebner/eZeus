#include "earrowspearbase.h"

eArrowSpearBase::eArrowSpearBase(eGameBoard& board,
                                 const eMissileTexs missileTexs,
                                 const eMissileType type,
                                 const std::vector<ePathPoint>& path) :
    eMissile(board, type, path),
    mTexs(missileTexs) {}

std::shared_ptr<eTexture>
eArrowSpearBase::getTexture(const eTileSize size) const {
    auto& board = this->board();
    const auto dir = board.direction();
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& rockTex = textures[id].*mTexs;
    const double a = angle();
    double da;
    if(dir == eWorldDirection::N) {
        da = 225;
    } else if(dir == eWorldDirection::E) {
        da = 315;
    } else if(dir == eWorldDirection::S) {
        da = 45;
    } else { // if(dir == eWorldDirection::W) {
        da = 135;
    }
    const int iid = std::round(((a - da)/11.25));
    const int texId = iid < 0 ? ((32 + iid) % 32) :
                                (iid % 32);
    return rockTex.getTexture(texId);
}
