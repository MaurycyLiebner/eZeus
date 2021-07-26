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

void eTile::setTerrain(const eTerrain& terr) {
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

eTypedSurroundings eTile::surroundings() const {
    eTerrain tlTerr = mTerr;
    eTerrain trTerr = mTerr;
    eTerrain brTerr = mTerr;
    eTerrain blTerr = mTerr;

    eTerrain tTerr = mTerr;
    eTerrain rTerr = mTerr;
    eTerrain bTerr = mTerr;
    eTerrain lTerr = mTerr;

    eTypedSurroundings result{mTerr, eSurroundings::end};

    if(mTopLeft) {
        tlTerr = mTopLeft->terrain();
    }
    if(mTopRight) {
        trTerr = mTopRight->terrain();
    }
    if(mBottomRight) {
        brTerr = mBottomRight->terrain();
    }
    if(mBottomLeft) {
        blTerr = mBottomLeft->terrain();
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

    if(tlTerr != mTerr) {
        result.fTerr = tlTerr;
    } else if(trTerr != mTerr) {
        result.fTerr = trTerr;
    } else if(brTerr != mTerr) {
        result.fTerr = brTerr;
    } else if(blTerr != mTerr) {
        result.fTerr = blTerr;
    } else if(tTerr != mTerr) {
        result.fTerr = tTerr;
    } else if(rTerr != mTerr) {
        result.fTerr = rTerr;
    } else if(bTerr != mTerr) {
        result.fTerr = bTerr;
    } else if(lTerr != mTerr) {
        result.fTerr = lTerr;
    }

    const bool tl = tlTerr != mTerr;
    const bool tr = trTerr != mTerr;
    const bool br = brTerr != mTerr;
    const bool bl = blTerr != mTerr;

    const bool t = tTerr != mTerr;
    const bool r = rTerr != mTerr;
    const bool b = bTerr != mTerr;
    const bool l = lTerr != mTerr;

    if(bl && br) {
        result.fSurr = eSurroundings::bottomLeftAndBottomRight;
    } else if(tr && br) {
        result.fSurr = eSurroundings::topRightAndBottomRight;
    } else if(tl && tr) {
        result.fSurr = eSurroundings::topLeftAndTopRight;
    } else if(tl && bl) {
        result.fSurr = eSurroundings::topLeftAndBottomLeft;
    } else if(br) {
        result.fSurr = eSurroundings::bottomRight;
    } else if(tr) {
        result.fSurr = eSurroundings::topRight;
    } else if(tl) {
        result.fSurr = eSurroundings::topLeft;
    } else if(bl) {
        result.fSurr = eSurroundings::bottomLeft;
    } else if(t) {
        result.fSurr = eSurroundings::top;
    } else if(r) {
        result.fSurr = eSurroundings::right;
    } else if(b) {
        result.fSurr = eSurroundings::bottom;
    } else if(l) {
        result.fSurr = eSurroundings::left;
    }

    return result;
}
