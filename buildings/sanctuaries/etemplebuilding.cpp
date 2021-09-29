#include "etemplebuilding.h"

#include "textures/egametextures.h"

eTempleBuilding::eTempleBuilding(const int id, eGameBoard& board) :
    eBuilding(board, eBuildingType::temple, 4, 4),
    mId(id) {
    setEnabled(true);
}

std::shared_ptr<eTexture>
eTempleBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    return blds.fSanctuary[mId].getTexture(2);
}

std::vector<eOverlay>
eTempleBuilding::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    eOverlay o;
    if(mId == 0) {
        o.fX = -0.45;
        o.fY = -2.75;
        const auto& coll = blds.fSanctuaryHOverlay;
        o.fTex = coll.getTexture(textureTime() % coll.size());
    } else {
        o.fX = -0.45;
        o.fY = -5.25;
        const auto& coll = blds.fSanctuaryWOverlay;
        o.fTex = coll.getTexture(textureTime() % coll.size());
    }
    return {o};
}
