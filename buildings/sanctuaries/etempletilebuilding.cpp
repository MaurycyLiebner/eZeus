#include "etempletilebuilding.h"

#include "textures/egametextures.h"

eTempleTileBuilding::eTempleTileBuilding(const int id, eGameBoard& board) :
    eSanctBuilding({0, 1, 0}, 1, board,
                   eBuildingType::templeTile, 1, 1),
    mId(id) {
    setEnabled(true);
}

std::shared_ptr<eTexture>
eTempleTileBuilding::getTexture(const eTileSize size) const {
    (void)size;
    return nullptr;
}

std::shared_ptr<eTexture>
eTempleTileBuilding::getTileTexture(const eTileSize size) const {
    const int p = progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = blds.fSanctuaryTiles;
    if(mId > 9) return coll.getTexture(mId - 10);
    return coll.getTexture(mId);
}

std::vector<eOverlay>
eTempleTileBuilding::getOverlays(const eTileSize size) const {
    const int p = progress();
    if(!p) return {};
    if(mId < 10) return {};
    eOverlay o;
    o.fX = 0.5;
    o.fY = -0.5;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = blds.fSanctuaryFire;
    o.fTex = coll.getTexture(textureTime() % coll.size());
    return {o};
}
