#include "egatehouse.h"

#include "textures/egametextures.h"

eGatehouse::eGatehouse(eGameBoard& board, const bool r) :
    eBuilding(board, eBuildingType::gatehouse,
              r ? 2 : 5, r ? 5 : 2),
    mRotated(r) {
    eGameTextures::loadGatehouseAndTower();
    setEnabled(true);
}

std::shared_ptr<eTexture>
eGatehouse::getTextureSides(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = mRotated ? blds.fGatehouseH :
                                  blds.fGatehouseW;
    return coll.getTexture(0);
}

eOverlay eGatehouse::getTextureEntrance(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = mRotated ? blds.fGatehouseH :
                                  blds.fGatehouseW;
    eOverlay o;
    o.fTex = coll.getTexture(1);
    o.fAlignTop = true;
    if(mRotated) {
        o.fX = 0.5;
        o.fY = 0.5;
    } else {
        o.fX = 1.5;
        o.fY = -0.5;
    }
    return o;
}

eOverlay eGatehouse::getTextureEntranceBack(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = mRotated ? blds.fGatehouseH :
                                  blds.fGatehouseW;
    eOverlay o;
    o.fTex = coll.getTexture(2);
    o.fAlignTop = true;
    if(mRotated) {
        o.fX = -0.5;
        o.fY = 0.5;
    } else {
        o.fX = 1.5;
        o.fY = -1.5;
    }
    return o;
}

eOverlay eGatehouse::getTextureEntranceOverlay(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = mRotated ? blds.fGatehouseH :
                                  blds.fGatehouseW;
    eOverlay o;
    o.fTex = coll.getTexture(3);
    o.fAlignTop = true;
    if(mRotated) {
        o.fX = 0.5;
        o.fY = -2.5;
    } else {
        o.fX = -1.45;
        o.fY = -0.65;
    }
    return o;
}
