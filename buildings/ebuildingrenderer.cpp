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

int eBuildingRenderer::spanW() const {
    return mBuilding->spanW();
}

int eBuildingRenderer::spanH() const {
    return mBuilding->spanH();
}

void eBuildingRenderer::draw(eTilePainter& p, const double x, const double y) {
    p.drawTexture(x, y, getTexture(p.size()), eAlignment::top);
    if(mBuilding->overlayEnabled()) {
        const auto overlays = getOverlays(p.size());
        for(const auto& o : overlays) {
            if(o.fAlignTop) p.drawTexture(x + o.fX, y + o.fY, o.fTex,
                                          eAlignment::top);
            else p.drawTexture(x + o.fX, y + o.fY, o.fTex);
        }
    }
}
