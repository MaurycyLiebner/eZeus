#include "epier.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

ePier::ePier(eGameBoard& board, const eOrientation o) :
    eBuilding(board, eBuildingType::pier, 2, 2),
    mO(o) {
    eGameTextures::loadPier();
}

std::shared_ptr<eTexture> ePier::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fPier1;
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto o = sRotated(mO, dir);
    int id = 3;
    switch(o) {
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
