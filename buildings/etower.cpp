#include "etower.h"

#include "textures/egametextures.h"

eTower::eTower(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::tower, 2, 2, 15) {}

std::shared_ptr<eTexture>
eTower::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    return texs[sizeId].fTower;
}
