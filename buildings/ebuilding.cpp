#include "ebuilding.h"

eBuilding::eBuilding(const eBuildingType type) :
    mSeed(rand()), mType(type) {}

void eBuilding::draw(eTilePainter& p,
                     const double x, const double y,
                     const eAlignment align) {
    p.drawTexture(x, y, getTexture(p.size()), align);
    const auto overlays = getOverlays(p.size());
    for(const auto& o : overlays) {
        p.drawTexture(x + o.fX, y + o.fY, o.fTex, align);
    }
}
