#include "etilebase.h"

#include "buildings/ebuilding.h"

void eTileBase::setWalkableElev(const bool w) {
    mWalkableElev = w;
}

void eTileBase::setElevation(const bool e) {
    mElevation = e;
}

void eTileBase::decResource(const int by) {
    setResource(mResource - by);
}

void eTileBase::setResource(const int r) {
    mResource = std::clamp(r, 0, 100);
}

void eTileBase::setBusy(const bool b) {
    mBusy = b;
}

void eTileBase::setMarbleLevel(const int l) {
    mMarbleLevel = l;
}

bool eTileBase::hasBridge() const {
    return hasRoad() && hasWater();
}

bool eTileBase::hasWater() const {
    return terrain() == eTerrain::water;
}

bool eTileBase::walkable() const {
    const auto t = underBuildingType();
    if(t == eBuildingType::road) return true;
    const auto terr = terrain() & eTerrain::walkable;
    if(!static_cast<bool>(terr)) return false;
    if(!mWalkableElev && mElevation) return false;
    return eBuilding::sWalkableBuilding(t);
}

void eTileBase::updateIsElevationTile() {
    const int a = altitude();
    for(int x = -1; x < 2; x++) {
        for(int y = -1; y < 2; y++) {
            if(x == 0 && y == 0) continue;
            const auto t = tileRel(x, y);
            if(!t) continue;
            const int ta = t->altitude();
            if(ta > a) {
                mElevation = true;
                return;
            }
        }
    }

    mElevation = false;
}

bool eTileBase::isShoreTile() const {
    if(mTerr != eTerrain::water) return false;
    for(int x = -1; x < 2; x++) {
        for(int y = -1; y < 2; y++) {
            if(x == 0 && y == 0) continue;
            const auto t = tileRel(x, y);
            if(!t) continue;
            if(t->terrain() != eTerrain::water) return true;
        }
    }

    return false;
}

double eTileBase::sDistance(eTileBase* const t1,
                            eTileBase* const t2) {
    const int dx = t1->x() - t2->x();
    const int dy = t1->y() - t2->y();
    return sqrt(dx*dx + dy*dy);
}

void eTileBase::setSeed(const int s) {
    mSeed = s;
}

void eTileBase::setDX(const int x) {
    mDX = x;
}

void eTileBase::setDY(const int y) {
    mDY = y;
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

void eTileBase::setAltitude(const int a, const bool update) {
    mAltitude = a;
    if(!update) return;
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            const auto t = tileRel<eTileBase>(dx, dy);
            if(!t) continue;
            t->updateIsElevationTile();
        }
    }
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

void eTileBase::read(eReadStream& src) {
    src >> mSeed;

    eTerrain terr;
    src >> terr;
    setTerrain(terr);

    src >> mScrub;

    int mlevel;
    src >> mlevel;
    setMarbleLevel(mlevel);

    src >> mAltitude;
    src >> mResource;
    src >> mElevation;
    src >> mWalkableElev;
    src >> mHasFish;
    src >> mRoadblock;
}

void eTileBase::write(eWriteStream& dst) const {
    dst << mSeed;
    dst << mTerr;
    dst << mScrub;
    dst << mMarbleLevel;
    dst << mAltitude;
    dst << mResource;
    dst << mElevation;
    dst << mWalkableElev;
    dst << mHasFish;
    dst << mRoadblock;
}

