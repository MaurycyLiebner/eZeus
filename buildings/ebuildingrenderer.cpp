#include "ebuildingrenderer.h"

eBuildingRenderer::eBuildingRenderer(const stdsptr<eBuilding>& b,
                                     const eBuildingRendererType type) :
    eObject(b->getBoard()),
    mBuilding(b),
    mType(type) {}

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

void eBuildingRenderer::draw(eTilePainter& p,
                             const double x, const double y,
                             const bool erase) {
    const auto tex = getTexture(p.size());
    if(tex) {
        if(erase) tex->setColorMod(255, 175, 255);
        p.drawTexture(x, y, tex, eAlignment::top);
        if(erase) tex->clearColorMod();
    }
    if(mBuilding->overlayEnabled()) {
        const auto overlays = getOverlays(p.size());
        for(const auto& o : overlays) {
            const auto& tex = o.fTex;
            const double dx = x + o.fX;
            const double dy = y + o.fY;
            if(erase) tex->setColorMod(255, 175, 255);
            if(o.fAlignTop) p.drawTexture(dx, dy, tex, eAlignment::top);
            else p.drawTexture(dx, dy, tex);
            if(erase) tex->clearColorMod();
        }
    }
}

void eBuildingRenderer::setTile(eTile* const tile) {
    mTile = tile;
}
