#include "ebuilding.h"

#include "engine/egameboard.h"

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

eTile* eBuilding::road(const eMoveDirection o) const {
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
        auto tt = u->tileRel(dx, dy);
        if(!tt) continue;
        if(tt->hasRoad()) return tt;
    }
    return nullptr;
}

void eBuilding::incTime(const int by) {
    for(int i = 0; i < by; i++) {
        mTime++;
        timeChanged();
    }
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
        p.drawTexture(x + o.fX, y + o.fY, o.fTex);
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
