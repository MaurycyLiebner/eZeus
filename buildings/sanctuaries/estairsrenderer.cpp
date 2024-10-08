#include "estairsrenderer.h"

#include "textures/egametextures.h"

eStairsRenderer::eStairsRenderer(
        const int id, const stdsptr<eBuilding>& b) :
    eBuildingRenderer(b, eBuildingRendererType::stairs),
    mId(id) {

}

std::shared_ptr<eTexture>
eStairsRenderer::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& terr = eGameTextures::terrain()[sizeId];
    return terr.fSanctuaryStairs.getTexture(mId);
}
