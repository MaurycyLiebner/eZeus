#include "epier.h"

#include "textures/egametextures.h"

ePier::ePier(eGameBoard& board, const eOrientation o) :
    eBuilding(board, eBuildingType::pier, 2, 2),
    mO(o) {}

std::shared_ptr<eTexture> ePier::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fPier1;
    int id = 3;
    switch(mO) {
    case eOrientation::topRight:
        id = 0;
        break;
    case eOrientation::bottomRight:
        id = 1;
        break;
    case eOrientation::bottomLeft:
        id = 2;
        break;
    case eOrientation::topLeft:
        id = 3;
        break;
    default:
        id = 0;
        break;
    }

    return coll.getTexture(id);
}

void ePier::erase() {
    if(mTradePost) {
        mTradePost->eBuilding::erase();
    }
    eBuilding::erase();
}

void ePier::setTradePost(eBuilding* const b) {
    mTradePost = b;
}
