#include "ebuilding.h"

#include "engine/egameboard.h"
#include "engine/etile.h"

eBuilding::eBuilding(eGameBoard& board,
                     const eBuildingType type,
                     const int sw, const int sh) :
    mBoard(board),
    mSeed(rand()), mType(type),
    mSpanW(sw), mSpanH(sh) {
    mBoard.registerBuilding(this);
}

eBuilding::~eBuilding() {
    mBoard.unregisterBuilding(this);
}

eTile* eBuilding::tileNeighbour(const eMoveDirection o,
                                const eTileValidator& v) const {
    if(!mTile) return nullptr;
    int dx = 0;
    int dy = 0;
    switch(o) {
    case eMoveDirection::topRight:
        dy--;
        break;
    case eMoveDirection::bottomRight:
        dx++;
        break;
    case eMoveDirection::bottomLeft:
        dy++;
        break;
    case eMoveDirection::topLeft:
        dx--;
        break;
    default:
        return nullptr;
    }
    for(const auto u : mUnderBuilding) {
        auto tt = static_cast<eTile*>(u->tileRel(dx, dy));
        if(!tt) continue;
        if(v(tt)) return tt;
    }
    return nullptr;
}

eTile* eBuilding::road(const eMoveDirection o) const {
    return tileNeighbour(o, [](eTile* const tile) {
        return tile->hasRoad();
    });
}

void eBuilding::incTime(const int by) {
    mTime += by;
    timeChanged(by);
}

void eBuilding::setTile(eTile* const t) {
    mTile = t;
}

void eBuilding::draw(eTilePainter& p,
                     const double x, const double y) {
    p.drawTexture(x, y, getTexture(p.size()), eAlignment::top);
    if(mOverlayEnabled()) {
        const auto overlays = getOverlays(p.size());
        for(const auto& o : overlays) {
            if(o.fAlignTop) p.drawTexture(x + o.fX, y + o.fY, o.fTex,
                                          eAlignment::top);
            else p.drawTexture(x + o.fX, y + o.fY, o.fTex);
        }
    }
}

void eBuilding::addUnderBuilding(eTile* const t) {
    mUnderBuilding.push_back(t);
}

void eBuilding::erase() {
    for(const auto t : mUnderBuilding) {
        t->setUnderBuilding(nullptr);
    }
    mUnderBuilding.clear();
    if(mTile) {
        mTile->setBuilding(nullptr);
        mTile = nullptr;
    }
}

void eBuilding::setEnabled(const bool e) {
    mEnabled = e;
}

void eBuilding::setOverlayEnabledFunc(const std::function<bool()>& e) {
    mOverlayEnabled = e;
}
