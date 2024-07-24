#include "ecolumn.h"

#include "textures/egametextures.h"
#include "textures/ebuildingtextures.h"
#include "engine/egameboard.h"

eDoricColumn::eDoricColumn(eGameBoard& board) :
    eColumn(board, &eBuildingTextures::fDoricColumn,
            eBuildingType::doricColumn, 1, 1) {
    eGameTextures::loadColumns();
}

eIonicColumn::eIonicColumn(eGameBoard& board) :
    eColumn(board, &eBuildingTextures::fIonicColumn,
            eBuildingType::ionicColumn, 1, 1) {
    eGameTextures::loadColumns();
}

eCorinthianColumn::eCorinthianColumn(eGameBoard& board) :
    eColumn(board, &eBuildingTextures::fCorinthianColumn,
            eBuildingType::corinthianColumn, 1, 1) {
    eGameTextures::loadColumns();
}

std::vector<eOverlay> eColumn::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& bds = eGameTextures::buildings();
    const auto& texs = bds[sizeId];
    const auto t = centerTile();
    auto& board = getBoard();
    const auto dir = board.direction();
    std::vector<eOverlay> os;
    if(const auto bl = t->bottomLeftRotated<eTile>(dir)) {
        if(bl->underBuildingType() == type()) {
            os.push_back(eOverlay{-1.95, -1.9, texs.fColumnConnectionH});
        }
    }
    if(const auto br = t->bottomRightRotated<eTile>(dir)) {
        if(br->underBuildingType() == type()) {
            os.push_back(eOverlay{-1.45, -2.4, texs.fColumnConnectionW});
        }
    }
    return os;
}
