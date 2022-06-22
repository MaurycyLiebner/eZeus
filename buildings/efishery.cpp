#include "efishery.h"

#include "textures/egametextures.h"

eFishery::eFishery(eGameBoard& board, const eOrientation o) :
    eResourceBuildingBase(board, eBuildingType::fishery,
                          2, 2, 10, eResourceType::fish),
    mO(o) {}

std::shared_ptr<eTexture> eFishery::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fFishery;
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

std::vector<eOverlay> eFishery::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    if(mBuildingBoat) {
        eOverlay o;
        const eTextureCollection* coll;
        switch(mO) {
        case eOrientation::topRight:
            coll = &blds.fFisheryBoatBuildingH;
            o.fX = 0.2;
            o.fY = -2.25;
            break;
        case eOrientation::bottomLeft:
            coll = &blds.fFisheryBoatBuildingH;
            o.fX = -0.3;
            o.fY = -2.38;
            break;
        default:
        case eOrientation::topLeft:
            coll = &blds.fFisheryBoatBuildingW;
            o.fX = 0.0;
            o.fY = -2.0;
            break;
        case eOrientation::bottomRight:
            coll = &blds.fFisheryBoatBuildingW;
            o.fX = -0.25;
            o.fY = -1.9;
            break;
        }

        const int texId = textureTime() % coll->size();
        o.fTex = coll->getTexture(texId);
        return {o};
    }
    return {};
}
