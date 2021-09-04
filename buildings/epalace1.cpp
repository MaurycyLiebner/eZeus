#include "epalace1.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "engine/egameboard.h"

ePalace1Base::ePalace1Base(eGameBoard& board) :
    eBuilding(board, eBuildingType::palace1, 4, 4) {
    board.registerPalace();
}

ePalace1Base::~ePalace1Base() {
    auto& b = getBoard();
    b.unregisterPalace();
}

std::shared_ptr<eTexture> ePalace1W::getTexture(const eTileSize size) const {
    const auto& texs = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    return texs[sizeId].fPalace1W;
}

std::shared_ptr<eTexture> ePalace1H::getTexture(const eTileSize size) const {
    const auto& texs = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    return texs[sizeId].fPalace1H;
}
