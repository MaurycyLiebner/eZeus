#include "etilebase.h"

#include "buildings/ebuilding.h"

void eTileBase::setWalkableElev(const bool w) {
    mWalkableElev = w;
}

void eTileBase::decResource(const int by) {
    mResource -= by;
}

void eTileBase::setResource(const int r) {
    mResource = r;
}

void eTileBase::setBusy(const bool b) {
    mBusy = b;
}

void eTileBase::setOnFire(const bool of) {
    mOnFire = of;
}

bool eTileBase::walkable() const {
    const auto terr = terrain() & eTerrain::walkable;
    if(!static_cast<bool>(terr)) return false;
    const auto t = underBuildingType();
    if(t == eBuildingType::none) return true;
    if(t == eBuildingType::vine) return true;
    if(t == eBuildingType::oliveTree) return true;
    if(t == eBuildingType::orangeTree) return true;
    if(t == eBuildingType::sheep) return true;
    if(t == eBuildingType::goat) return true;
    return false;
}

bool eTileBase::isElevationTile() const {
    const int a = altitude();
    for(int x = -1; x < 2; x++) {
        for(int y = -1; y < 2; y++) {
            if(x == 0 && y == 0) continue;
            const auto t = tileRel(x, y);
            if(!t) continue;
            const int ta = t->altitude();
            if(ta > a) return true;
        }
    }

    return false;
}

void eTileBase::setSeed(const int s) {
    mSeed = s;
}

void eTileBase::setX(const int x) {
    mX = x;
}

void eTileBase::setY(const int y) {
    mY = y;
}

std::vector<eTileBase::eTO> eTileBase::neighbours(const eTileVerifier& v) const {
    std::vector<eTileBase::eTO> result;
    for(int i = 0; i < 8; i++) {
        const auto o = static_cast<eOrientation>(i);
        const auto t = neighbour(o);
        if(!t) continue;
        if(v(t)) result.push_back({o, t});
    }
    return result;
}

eTileBase::eTO eTileBase::randomNeighbour(const eTileVerifier& v) const {
    const auto ts = neighbours(v);
    if(ts.empty()) return {eOrientation::top, nullptr};
    return ts[rand() % ts.size()];
}

std::vector<eTileBase::eTO> eTileBase::diagonalNeighbours(const eTileVerifier& v) const {
    std::vector<eTileBase::eTO> result;
    for(int i = 0; i < 8; i += 2) {
        const auto o = static_cast<eOrientation>(i);
        const auto t = neighbour(o);
        if(!t) continue;
        if(v(t)) result.push_back({o, t});
    }
    return result;
}

eTileBase::eTO eTileBase::randomDiagonalNeighbour(const eTileVerifier& v) const {
    const auto ts = diagonalNeighbours(v);
    if(ts.empty()) return {eOrientation::top, nullptr};
    return ts[rand() % ts.size()];
}

void eTileBase::setAltitude(const int a) {
    mAltitude = a;
}

void eTileBase::setTerrain(const eTerrain terr) {
    mTerr = terr;
}

void eTileBase::setScrub(const double s) {
    mScrub = std::clamp(s, 0., 1.);
}

void eTileBase::incScrub(const double s) {
    setScrub(mScrub + s);
}

void eTileBase::setTopLeft(eTileBase* const tl) {
    mTopLeft = tl;
}

void eTileBase::setTopRight(eTileBase* const tr) {
    mTopRight = tr;
}

void eTileBase::setBottomRight(eTileBase* const br) {
    mBottomRight = br;
}

void eTileBase::setBottomLeft(eTileBase* const bl) {
    mBottomLeft = bl;
}
