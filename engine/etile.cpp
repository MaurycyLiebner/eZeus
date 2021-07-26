#include "etile.h"

#include <random>

int gId = 0;

eTile::eTile(const int x, const int y) :
    mId(gId++), mX(x), mY(y) {}

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

void eTile::setTerrain(const eTerrain terr) {
    mTerr = terr;
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

void eTile::neighboursWithTerrain(const eTerrain terr,
                                  bool& tl, bool& tr,
                                  bool& br, bool& bl,
                                  bool& t, bool& r,
                                  bool& b, bool& l) const {
    eTerrain tlTerr = mTerr;
    eTerrain trTerr = mTerr;
    eTerrain brTerr = mTerr;
    eTerrain blTerr = mTerr;

    eTerrain tTerr = mTerr;
    eTerrain rTerr = mTerr;
    eTerrain bTerr = mTerr;
    eTerrain lTerr = mTerr;

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

    tl = tlTerr != terr;
    tr = trTerr != terr;
    br = brTerr != terr;
    bl = blTerr != terr;

    t = tTerr != terr;
    r = rTerr != terr;
    b = bTerr != terr;
    l = lTerr != terr;
}
