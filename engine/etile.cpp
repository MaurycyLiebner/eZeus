#include "etile.h"

#include <random>
#include <algorithm>

#include "buildings/ebuilding.h"

eTile::eTile(const int x, const int y) {
    setSeed(rand());
    setX(x);
    setY(y);
}

int eTile::scrubId(const int nLevels) const {
    const double div = 1./nLevels;
    const int i = std::round(scrub()/div);
    return std::clamp(i, 0, nLevels);
}

std::vector<eTile*> eTile::surroundingRoads() const {
    std::vector<eTile*> tiles;
    for(int i = 0; i < 8; i += 2) {
        const auto o = static_cast<eOrientation>(i);
        const auto n = neighbour(o);
        const auto nt = static_cast<eTile*>(n);
        if(n && nt->hasRoad()) tiles.push_back(nt);
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
    tlTerr = terrain();
    trTerr = tlTerr;
    brTerr = tlTerr;
    blTerr = tlTerr;

    tTerr = tlTerr;
    rTerr = tlTerr;
    bTerr = tlTerr;
    lTerr = tlTerr;

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
    const auto terr = terrain() & eTerrain::walkable;
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
