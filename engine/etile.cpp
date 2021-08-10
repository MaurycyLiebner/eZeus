#include "etile.h"

#include <random>
#include <algorithm>

#include "buildings/ebuilding.h"

eTile::eTile(const int x, const int y) :
    mSeed(rand()), mX(x), mY(y) {}

int eTile::scrubId(const int nLevels) const {
    const double div = 1./nLevels;
    const int i = std::round(mScrub/div);
    return std::clamp(i, 0, nLevels);
}

eTile* eTile::left() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->topLeft();
}

eTile* eTile::top() const {
    if(!mTopLeft) return nullptr;
    return mTopLeft->topRight();
}

eTile* eTile::right() const {
    if(!mTopRight) return nullptr;
    return mTopRight->bottomRight();
}

eTile* eTile::bottom() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->bottomRight();
}

std::vector<eTile::eTO> eTile::neighbours(const eTileVerifier& v) const {
    std::vector<eTile::eTO> result;
    for(int i = 0; i < 8; i++) {
        const auto o = static_cast<eOrientation>(i);
        const auto t = neighbour(o);
        if(!t) continue;
        if(v(t)) result.push_back({o, t});
    }
    return result;
}

eTile::eTO eTile::randomNeighbour(const eTileVerifier& v) const {
    const auto ts = neighbours(v);
    if(ts.empty()) return {eOrientation::top, nullptr};
    return ts[rand() % ts.size()];
}

std::vector<eTile::eTO> eTile::diagonalNeighbours(const eTileVerifier& v) const {
    std::vector<eTile::eTO> result;
    for(int i = 0; i < 8; i += 2) {
        const auto o = static_cast<eOrientation>(i);
        const auto t = neighbour(o);
        if(!t) continue;
        if(v(t)) result.push_back({o, t});
    }
    return result;
}

eTile::eTO eTile::randomDiagonalNeighbour(const eTileVerifier& v) const {
    const auto ts = diagonalNeighbours(v);
    if(ts.empty()) return {eOrientation::top, nullptr};
    return ts[rand() % ts.size()];
}

eTile* eTile::neighbour(const eOrientation o) const {
    switch(o) {
    case eOrientation::topRight: {
        return topRight();
    } break;
    case eOrientation::right: {
        return right();
    } break;
    case eOrientation::bottomRight: {
        return bottomRight();
    } break;
    case eOrientation::bottom: {
        return bottom();
    } break;
    case eOrientation::bottomLeft: {
        return bottomLeft();
    } break;
    case eOrientation::left: {
        return left();
    } break;
    case eOrientation::topLeft: {
        return topLeft();
    } break;
    case eOrientation::top: {
        return top();
    } break;
    }
    return nullptr;
}

eTile* eTile::tileRel(const int x, const int y) {
    if(x == 0 && y == 0) return this;
    if(x > 0) {
        const auto br = bottomRight();
        if(!br) return nullptr;
        return br->tileRel(x - 1, y);
    } else if(x < 0) {
        const auto tl = topLeft();
        if(!tl) return nullptr;
        return tl->tileRel(x + 1, y);
    }
    if(y > 0) {
        const auto bl = bottomLeft();
        if(!bl) return nullptr;
        return bl->tileRel(x, y - 1);
    } else if(y < 0) {
        const auto tl = topRight();
        if(!tl) return nullptr;
        return tl->tileRel(x, y + 1);
    }
    return nullptr;
}

eTile* eTile::tileAbs(const int x, const int y) {
    return tileRel(x - mX, y - mY);
}

void eTile::setAltitude(const int a) {
    mAltitude = a;
}

void eTile::setTerrain(const eTerrain terr) {
    mTerr = terr;
}

void eTile::setScrub(const double s) {
    mScrub = std::clamp(s, 0., 1.);
}

void eTile::incScrub(const double s) {
    setScrub(mScrub + s);
}

void eTile::setTopLeft(eTile* const tl) {
    mTopLeft = tl;
}

void eTile::setTopRight(eTile* const tr) {
    mTopRight = tr;
}

void eTile::setBottomRight(eTile* const br) {
    mBottomRight = br;
}

void eTile::setBottomLeft(eTile* const bl) {
    mBottomLeft = bl;
}

std::vector<eTile*> eTile::surroundingRoads() const {
    std::vector<eTile*> tiles;
    for(int i = 0; i < 8; i += 2) {
        const auto o = static_cast<eOrientation>(i);
        const auto n = neighbour(o);
        if(n && n->hasRoad()) tiles.push_back(n);
    }
    return tiles;
}

eTile* eTile::nearestRoad() const {
    const auto tiles = surroundingRoads();
    if(tiles.empty()) return nullptr;
    return tiles[rand() % tiles.size()];
}

void eTile::surroundingTerrain(eTerrain& tlTerr,
                               eTerrain& trTerr,
                               eTerrain& brTerr,
                               eTerrain& blTerr,
                               eTerrain& tTerr,
                               eTerrain& rTerr,
                               eTerrain& bTerr,
                               eTerrain& lTerr) const {
    tlTerr = mTerr;
    trTerr = mTerr;
    brTerr = mTerr;
    blTerr = mTerr;

    tTerr = mTerr;
    rTerr = mTerr;
    bTerr = mTerr;
    lTerr = mTerr;

    {
        const auto tl = topLeft();
        if(tl) {
            tlTerr = tl->terrain();
        }
    }
    {
        const auto tr = topRight();
        if(tr) {
            trTerr = tr->terrain();
        }
    }
    {
        const auto br = bottomRight();
        if(br) {
            brTerr = br->terrain();
        }
    }
    {
        const auto bl = bottomLeft();
        if(bl) {
            blTerr = bl->terrain();
        }
    }

    {
        const auto t = top();
        if(t) {
            tTerr = t->terrain();
        }
    }

    {
        const auto r = right();
        if(r) {
            rTerr = r->terrain();
        }
    }

    {
        const auto b = bottom();
        if(b) {
            bTerr = b->terrain();
        }
    }

    {
        const auto l = left();
        if(l) {
            lTerr = l->terrain();
        }
    }
}

void eTile::neighboursWithTerrain(const eTerrain terr,
                                  bool& tl, bool& tr,
                                  bool& br, bool& bl,
                                  bool& t, bool& r,
                                  bool& b, bool& l) const {
    eTerrain tlTerr;
    eTerrain trTerr;
    eTerrain brTerr;
    eTerrain blTerr;

    eTerrain tTerr;
    eTerrain rTerr;
    eTerrain bTerr;
    eTerrain lTerr;

    surroundingTerrain(tlTerr, trTerr, brTerr, blTerr,
                       tTerr, rTerr, bTerr, lTerr);

    tl = tlTerr != terr;
    tr = trTerr != terr;
    br = brTerr != terr;
    bl = blTerr != terr;

    t = tTerr != terr;
    r = rTerr != terr;
    b = bTerr != terr;
    l = lTerr != terr;
}

void eTile::addCharacter(eCharacter* const c) {
    mCharacters.push_back(c);
}

bool eTile::removeCharacter(eCharacter* const c) {
    const auto it = std::find(mCharacters.begin(), mCharacters.end(), c);
    if(it == mCharacters.end()) return false;
    mCharacters.erase(it);
    return true;
}

bool eTile::walkable() const {
    const auto terr = mTerr & eTerrain::walkable;
    if(!static_cast<bool>(terr)) return false;
    if(underBuilding() && !hasRoad()) return false;
    return true;
}

void eTile::setBuilding(eBuilding* const b) {
    mBuilding = b;
    if(b) b->setTile(this);
}

bool eTile::hasRoad() const {
    if(!mBuilding) return false;
    return mBuilding->type() == eBuildingType::road;
}

void eTile::setUnderBuilding(eBuilding* const b) {
    mUnderBuilding = b;
}

void eTile::setSpawner(eSpawner* const s) {
    mSpawner = s;
}

void eTile::setDrawnSpan(const int w, const int h) {
    mDrawnSpanW = w;
    mDrawnSpanH = h;
}

void eTile::setWalkableElev(const bool w) {
    mWalkableElev = w;
}

void eTile::decResource(const int by) {
    mResource -= by;
}
