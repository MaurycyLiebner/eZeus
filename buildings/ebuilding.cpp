#include "ebuilding.h"

eBuilding::eBuilding(const eBuildingType type,
                     const int sw, const int sh) :
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {}

void eBuilding::setTile(eTile* const t) {
    mTile = t;
}

void eBuilding::draw(eTilePainter& p,
                     const double x, const double y,
                     const eAlignment align) {
    p.drawTexture(x, y, getTexture(p.size()), align);
    const auto overlays = getOverlays(p.size());
    for(const auto& o : overlays) {
        p.drawTexture(x + o.fX, y + o.fY, o.fTex, align);
    }
}
