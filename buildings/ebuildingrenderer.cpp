#include "ebuildingrenderer.h"

eBuildingRenderer::eBuildingRenderer(const stdsptr<eBuilding>& b) :
    eObject(b->getBoard()),
    mBuilding(b) {}

std::shared_ptr<eTexture>
eBuildingRenderer::getTexture(const eTileSize size) const {
    return mBuilding->getTexture(size);
}

std::vector<eOverlay>
eBuildingRenderer::getOverlays(const eTileSize size) const {
    return mBuilding->getOverlays(size);
}
