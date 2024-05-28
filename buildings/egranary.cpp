#include "egranary.h"

#include "textures/egametextures.h"

eGranary::eGranary(eGameBoard& board) :
    eStorageBuilding(board, eBuildingType::granary,
                     4, 4, 18, eResourceType::food),
    mTextures(eGameTextures::buildings()) {
    eGameTextures::loadGranary();
    setOverlayEnabledFunc([]() { return true; });
}

std::shared_ptr<eTexture> eGranary::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fGranary;
}

std::vector<eOverlay> eGranary::getOverlays(const eTileSize size) const {
    std::vector<eOverlay> os;
    const int sizeId = static_cast<int>(size);
    const auto& texs = mTextures[sizeId];
    if(enabled()) {
        const auto& coll = texs.fGranaryOverlay;
        const int texId = textureTime() % coll.size();
        auto& o = os.emplace_back();
        o.fTex = coll.getTexture(texId);
        o.fX = 0.38;
        o.fY = -3.78;
    }
    const std::pair<double, double> xy[8] = {{-3.11, -5.1},
                                             {-3, -5.65},
                                             {-2.89, -6.25},

                                             {-2.64, -4.43},
                                             {-2.53, -5.00},
                                             {-2.42, -5.55},
                                             {-2.31, -6.13},
                                             {-2.20, -6.73}};
    for(int i = 0; i < 8; i++) {
        const int count = resourceCount(i);
        if(count <= 0) continue;
        const auto type = resourceType(i);
        if(type == eResourceType::none) continue;
        eOverlay& o = os.emplace_back();
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
        case eResourceType::oranges:
            o.fTex = texs.fGranaryOranges;
            break;
        default: continue;
        }
        o.fX = xy[i].first;
        o.fY = xy[i].second;
    }
    return os;
}
