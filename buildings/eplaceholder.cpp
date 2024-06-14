#include "eplaceholder.h"

ePlaceholder::ePlaceholder(eGameBoard& board) :
    eBuilding(board, eBuildingType::placeholder, 1, 1) {}

stdsptr<eTexture> ePlaceholder::getTexture(const eTileSize size) const {
    (void)size;
    return nullptr;
}

void ePlaceholder::erase() {}

void ePlaceholder::sanctuaryErase() {
    eBuilding::erase();
}
