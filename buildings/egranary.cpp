#include "egranary.h"

#include "textures/egametextures.h"

eGranary::eGranary(eGameBoard& board) :
    eStorageBuilding(board, eBuildingType::granary, 4, 4),
    mTextures(eGameTextures::buildings()) {

}

eTexture eGranary::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fGranary;
}

std::vector<eOverlay> eGranary::getOverlays(const eTileSize size) const {
    std::vector<eOverlay> os;
    const int sizeId = static_cast<int>(size);
    const auto texs = mTextures[sizeId];
    const auto& coll = texs.fGranaryOverlay;
    const int texId = textureTime() % coll.size();
    auto& o = os.emplace_back();
    o.fTex = coll.getTexture(texId);
    o.fX = 0.5;
    o.fY = -3.81;
    for(int i = 0; i < 8; i++) {
        const int count = resourceCount(i);
        if(count <= 0) continue;
        const auto type = resourceType(i);
        if(type == eResourceType::none) continue;
        eOverlay& o = os.emplace_back();
        const auto texs = mTextures[sizeId];
        switch(type) {
        case eResourceType::urchin:
            o.fTex = texs.fGranaryUrchin;
            break;
        case eResourceType::fish:
            o.fTex = texs.fGranaryFish;
            break;
        case eResourceType::meat:
            o.fTex = texs.fGranaryMeat;
            break;
        case eResourceType::cheese:
            o.fTex = texs.fGranaryCheese;
            break;
        case eResourceType::carrots:
            o.fTex = texs.fGranaryCarrots;
            break;
        case eResourceType::onions:
            o.fTex = texs.fGranaryOnions;
            break;
        case eResourceType::wheat:
            o.fTex = texs.fGranaryWheat;
            break;
        default: continue;
        }
        o.fX = -0.5;
        o.fY = -2;
    }
    return os;
}
