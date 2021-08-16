#include "etilebase.h"

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

void eTileBase::setSeed(const int s) {
    mSeed = s;
}

void eTileBase::setX(const int x) {
    mX = x;
}

void eTileBase::setY(const int y) {
    mY = y;
}

eTileBase* eTileBase::left() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->topLeft();
}

eTileBase* eTileBase::top() const {
    if(!mTopLeft) return nullptr;
    return mTopLeft->topRight();
}

eTileBase* eTileBase::right() const {
    if(!mTopRight) return nullptr;
    return mTopRight->bottomRight();
}

eTileBase* eTileBase::bottom() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->bottomRight();
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

eTileBase* eTileBase::neighbour(const eOrientation o) const {
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

eTileBase* eTileBase::tileRel(const int x, const int y) {
    if(x == 0 && y == 0) return static_cast<eTileBase*>(this);
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

eTileBase* eTileBase::tileAbs(const int x, const int y) {
    return tileRel(x - mX, y - mY);
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
