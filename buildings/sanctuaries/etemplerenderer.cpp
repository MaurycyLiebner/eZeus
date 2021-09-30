#include "etemplerenderer.h"

#include "textures/egametextures.h"

eTempleRenderer::eTempleRenderer(
        const int id,
        const stdsptr<eTempleBuilding>& b) :
    eBuildingRenderer(b), mId(id), mB(b) {}

std::shared_ptr<eTexture> eTempleRenderer::getTexture(const eTileSize size) const {
    const int p = mB->progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const int id = p - 1;
    const auto& coll = blds.fSanctuary[mId];
    return coll.getTexture(id);
}

std::vector<eOverlay> eTempleRenderer::getOverlays(const eTileSize size) const {
    const int p = mB->progress();
    if(p < 2) {
        return {};
    }
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const int tt = mB->textureTime();
    eOverlay o;
    if(mId == 0) {
        o.fX = -0.45;
        o.fY = -2.75;
        const auto& coll = blds.fSanctuaryHOverlay;
        o.fTex = coll.getTexture(tt % coll.size());
    } else {
        o.fX = -0.45;
        o.fY = -5.25;
        const auto& coll = blds.fSanctuaryWOverlay;
        o.fTex = coll.getTexture(tt % coll.size());
    }
    return {o};
}
