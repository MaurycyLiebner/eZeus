#include "epalacerenderer.h"

ePalace1Renderer::ePalace1Renderer(
        const stdsptr<ePalace>& b) :
    eBuildingRenderer(b, eBuildingRendererType::palace1),
    mPalace(b) {}

std::shared_ptr<eTexture>
ePalace1Renderer::getTexture(const eTileSize size) const {
    return mPalace->getTexture1(size);
}

std::vector<eOverlay>
ePalace1Renderer::getOverlays(const eTileSize) const {
    return {};
}

ePalace2Renderer::ePalace2Renderer(
        const stdsptr<ePalace>& b) :
    eBuildingRenderer(b, eBuildingRendererType::palace2),
    mPalace(b) {}

std::shared_ptr<eTexture>
ePalace2Renderer::getTexture(const eTileSize size) const {
    return mPalace->getTexture2(size);
}

std::vector<eOverlay>
ePalace2Renderer::getOverlays(const eTileSize size) const {
    return mPalace->getOverlays2(size);
}
