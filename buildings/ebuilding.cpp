#include "ebuilding.h"

eBuilding::eBuilding(const eBuildingType type,
                     const int sw, const int sh) :
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {}

std::vector<eTile*> eBuilding::surroundingRoads() const {
    if(!mTile) return std::vector<eTile*>();
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
    return tiles;
}

eTile* eBuilding::nearestRoad() const {
    const auto tiles = surroundingRoads();
    if(tiles.empty()) return nullptr;
    return tiles[rand() % tiles.size()];
}

eTile* eBuilding::road(const eOrientation o) const {
    if(!mTile) return nullptr;
    const int tx = mTile->x();
    const int ty = mTile->y();
    int xMin = tx;
    int xMax = tx;
    int yMin = ty;
    int yMax = ty;
    switch(o) {
    case eOrientation::topRight: {
        if(mSpanW == 1 && mSpanH == 1) {
            yMin -= 1;
        } if(mSpanW == 2 && mSpanH == 2) {
            yMin -= 1;
            xMax += 1;
        } else if(mSpanW == 3 && mSpanH == 3) {
            yMin -= 2;
            xMin -= 1;
            xMax += 1;
        }
        yMax = yMin;
    } break;
    case eOrientation::bottomRight: {
        if(mSpanW == 1 && mSpanH == 1) {
            xMin += 1;
        } if(mSpanW == 2 && mSpanH == 2) {
            xMin += 2;
            yMax += 1;
        } else if(mSpanW == 3 && mSpanH == 3) {
            xMin += 2;
            yMin -= 1;
            yMax += 1;
        }
        xMax = xMin;
    } break;
    case eOrientation::bottomLeft: {
        if(mSpanW == 1 && mSpanH == 1) {
            yMin += 1;
        } if(mSpanW == 2 && mSpanH == 2) {
            yMin += 2;
            xMax += 1;
        } else if(mSpanW == 3 && mSpanH == 3) {
            yMin += 2;
            xMin -= 1;
            xMax += 1;
        }
        yMax = yMin;
    } break;
    case eOrientation::topLeft: {
        if(mSpanW == 1 && mSpanH == 1) {
            xMin -= 1;
        } if(mSpanW == 2 && mSpanH == 2) {
            xMin -= 1;
            yMax += 1;
        } else if(mSpanW == 3 && mSpanH == 3) {
            xMin += 2;
            yMin -= 1;
            yMax += 1;
        }
        xMax = xMin;
    } break;
    default: return nullptr;
    }
    for(int x = xMin; x <= xMax; x++) {
        for(int y = yMin; y <= yMax; y++) {
            const auto t = mTile->tileAbs(x, y);
            if(t && t->hasRoad()) return t;
        }
    }
    return nullptr;
}

void eBuilding::incTime(const int by) {
    mTime += by;
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
