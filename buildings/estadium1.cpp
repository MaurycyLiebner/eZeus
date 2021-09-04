#include "estadium1.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "engine/egameboard.h"

eStadium1Base::eStadium1Base(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::stadium1, 5, 5, 45) {
    board.registerStadium();
}

eStadium1Base::~eStadium1Base() {
    auto& b = getBoard();
    b.unregisterStadium();
}

std::shared_ptr<eTexture> eStadium1W::getTexture(const eTileSize size) const {
    const auto& texs = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    return texs[sizeId].fStadium1W;
}

std::shared_ptr<eTexture> eStadium1H::getTexture(const eTileSize size) const {
    const auto& texs = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    return texs[sizeId].fStadium1H;
}
