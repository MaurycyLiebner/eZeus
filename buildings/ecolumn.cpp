#include "ecolumn.h"

#include "textures/egametextures.h"
#include "textures/ebuildingtextures.h"

eDoricColumn::eDoricColumn(eGameBoard& board) :
    eColumn(board, &eBuildingTextures::fDoricColumn,
            eBuildingType::doricColumn, 1, 1) {

}

eIonicColumn::eIonicColumn(eGameBoard& board) :
    eColumn(board, &eBuildingTextures::fIonicColumn,
            eBuildingType::ionicColumn, 1, 1) {

}

eCorinthianColumn::eCorinthianColumn(eGameBoard& board) :
    eColumn(board, &eBuildingTextures::fCorinthianColumn,
            eBuildingType::corinthianColumn, 1, 1) {

}

std::vector<eOverlay> eColumn::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& bds = eGameTextures::buildings();
    const auto& texs = bds[sizeId];
    const auto t = centerTile();
    std::vector<eOverlay> os;
    if(const auto bl = t->bottomLeft<eTile>()) {
        if(bl->underBuildingType() == type()) {
            os.push_back(eOverlay{-1.95, -1.9, texs.fColumnConnectionH});
        }
    }
    if(const auto br = t->bottomRight<eTile>()) {
        if(br->underBuildingType() == type()) {
            os.push_back(eOverlay{-1.45, -2.4, texs.fColumnConnectionW});
        }
    }
    return os;
}
