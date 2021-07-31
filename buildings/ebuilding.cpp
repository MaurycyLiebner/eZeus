#include "ebuilding.h"

eBuilding::eBuilding(const eBuildingType type,
                     const int sw, const int sh) :
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {}

eTile* eBuilding::nearestRoad() const {
    if(!mTile) return nullptr;
    const int tx = mTile->x();
    const int ty = mTile->y();
    std::vector<eTile*> tiles;
    int xMin = tx;
    int xMax = tx;
    int yMin = ty;
    int yMax = ty;
    if(mSpanW == 2 && mSpanH == 2) {
        xMax++;
        yMax++;
    } else if(mSpanW == 3 && mSpanH == 3) {
        xMin--;
        yMin--;
        xMax++;
        yMax++;
    }
    for(int x = xMin; x <= xMax; x++) {
        for(int y = yMin; y <= yMax; y++) {
            const auto t = mTile->tileRel(x, y);
            if(!t) continue;
            const auto r = t->nearestRoad();
            if(r) tiles.push_back(r);
        }
    }
    if(tiles.empty()) return nullptr;
    return tiles[rand() % tiles.size()];
}

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
