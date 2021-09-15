#include "estadiumrenderer.h"

eStadium1Renderer::eStadium1Renderer(
        const stdsptr<eStadium>& b) :
    eBuildingRenderer(b),
    mStadium(b) {}

std::shared_ptr<eTexture>
eStadium1Renderer::getTexture(const eTileSize size) const {
    return mStadium->getTexture1(size);
}

std::vector<eOverlay>
eStadium1Renderer::getOverlays(const eTileSize) const {
    return {};
}

eStadium2Renderer::eStadium2Renderer(
        const stdsptr<eStadium>& b) :
    eBuildingRenderer(b),
    mStadium(b) {}

std::shared_ptr<eTexture>
eStadium2Renderer::getTexture(const eTileSize size) const {
    return mStadium->getTexture2(size);
}

std::vector<eOverlay>
eStadium2Renderer::getOverlays(const eTileSize size) const {
    return mStadium->getOverlays2(size);
}
