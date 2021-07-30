#include "etile.h"

#include <random>
#include <algorithm>

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
