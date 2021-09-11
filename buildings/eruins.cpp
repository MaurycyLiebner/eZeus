#include "eruins.h"

#include "textures/egametextures.h"

eRuins::eRuins(eGameBoard& board) :
    eBuilding(board, eBuildingType::ruins, 1, 1) {

}

stdsptr<eTexture> eRuins::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::terrain();
    const auto& coll = texs[sizeId].fTinyStones;
    return coll.getTexture(seed() % coll.size());
}
