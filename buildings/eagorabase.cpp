#include "eagorabase.h"

#include "eagoraspace.h"
#include "ebuildingrenderer.h"
#include "engine/egameboard.h"

#include "efoodvendor.h"
#include "efleecevendor.h"
#include "eoilvendor.h"
#include "ewinevendor.h"
#include "earmsvendor.h"
#include "ehorsevendor.h"

#include "eroad.h"

#include "characters/epeddler.h"

eAgoraBase::eAgoraBase(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int nPts) :
    ePatrolBuildingBase(board,
                        [this]() { return e::make_shared<ePeddler>(getBoard(), this); },
                        type, sw, sh, 0),
    mNPts(nPts) {
    for(int i = 0; i < mNPts; i++) {
        mBs.push_back(nullptr);
    }
}

void eAgoraBase::erase() {
    for(const auto& b : mBs) {
        b->erase();
    }
    for(int i = 0; i < mNPts; i++) {
        setBuilding(i, nullptr);
    }
    const auto& brd = getBoard();
    const auto rect = tileRect();
    for(int x = rect.x; x < rect.x + rect.w; x++) {
        for(int y = rect.y; y < rect.y + rect.h; y++) {
            const auto t = brd.tile(x, y);
            if(!t) continue;
            const auto ub = t->underBuilding();
            if(!ub) continue;
            if(ub->type() == eBuildingType::road) {
                const auto r = static_cast<eRoad*>(ub);
                r->setUnderAgora(nullptr);
            }
        }
    }
    eBuilding::erase();
}

SDL_Point eAgoraBase::pt(const int rx, const int ry,
                         const eAgoraOrientation o,
                         const int id) const {
    int dx;
    int dy;
    int ddx;
    int ddy;
    switch(o) {
    case eAgoraOrientation::bottomLeft:
        dx = 0;
        dy = 2;
        ddx = 2;
        ddy = 0;
        break;
    case eAgoraOrientation::topRight:
        dx = 0;
        dy = 1;
        ddx = 2;
        ddy = 0;
        break;
    case eAgoraOrientation::bottomRight:
        dx = 1;
        dy = 1;
        ddx = 0;
        ddy = 2;
        break;
    case eAgoraOrientation::topLeft:
        dx = 0;
        dy = 1;
        ddx = 0;
        ddy = 2;
        break;
    }

    const int tx = rx + dx + id*ddx;
    const int ty = ry + dy + id*ddy;
    return {tx, ty};
}

eBuilding* eAgoraBase::building(const int id) const {
    return mBs[id].get();
}

void eAgoraBase::setBuilding(const int id, const stdsptr<eBuilding>& b) {
    mBs[id] = b;
    if(!b) return;
    auto& brd = getBoard();
    const auto p = pt(id);
    const auto tile = brd.tile(p.x, p.y);
    tile->setBuilding(e::make_shared<eBuildingRenderer>(b));
    b->setCenterTile(tile);
    const int minX = p.x;
    const int minY = p.y - 1;
    const int maxX = minX + 2;
    const int maxY = minY + 2;
    b->setTileRect({minX, minY, 2, 2});
    for(int i = minX; i < maxX; i++) {
        for(int j = minY; j < maxY; j++) {
            const auto t = brd.tile(i, j);
            b->addUnderBuilding(t);
            t->setUnderBuilding(b);
        }
    }
}

void eAgoraBase::setBuilding(eBuilding* const space, const stdsptr<eBuilding>& b) {
    bool found = false;
    int id = -1;
    for(const auto& bb : mBs) {
        id++;
        if(bb.get() == space) {
            found = true;
            break;
        }
    }
    if(!found) return;
    setBuilding(id, b);
}

void eAgoraBase::fillSpaces() {
    auto& brd = getBoard();
    for(int i = 0; i < mNPts; i++) {
        const auto b = building(i);
        if(b) continue;
        const auto space = e::make_shared<eAgoraSpace>(
                               ref<eAgoraBase>(), brd);
        setBuilding(i, space);
    }
}

bool eAgoraBase::hasVendors() const {
    for(const auto& b : mBs) {
        if(!b) continue;
        const auto t = b->type();
        if(t == eBuildingType::agoraSpace) continue;
        return true;
    }
    return false;
}

void eAgoraBase::agoraProvide(eBuilding* const b) {
    if(!b) return;
    const auto bt = b->type();
    if(bt != eBuildingType::commonHouse &&
       bt != eBuildingType::eliteHousing) return;
    for(int i = 0; i < mNPts; i++) {
        const auto fvb = building(i);
        if(!fvb) continue;
        const auto bt = fvb->type();
        switch(bt) {
        case eBuildingType::foodVendor:
        case eBuildingType::fleeceVendor:
        case eBuildingType::oilVendor:
        case eBuildingType::armsVendor:
        case eBuildingType::wineVendor:
        case eBuildingType::horseTrainer: {
            const auto fv = static_cast<eVendor*>(fvb);
            const int r = fv->peddlerResource();
            if(r <= 0) continue;
            const int rr = b->provide(fv->provideType(), r);
            fv->takeForPeddler(rr);
        } break;
        default: break;
        }
    }
}

int eAgoraBase::agoraCount(const eProvide r) const {
    for(int i = 0; i < mNPts; i++) {
        const auto fvb = building(i);
        if(!fvb) continue;
        const auto bt = fvb->type();
        switch(bt) {
        case eBuildingType::foodVendor:
        case eBuildingType::fleeceVendor:
        case eBuildingType::oilVendor:
        case eBuildingType::armsVendor:
        case eBuildingType::wineVendor:
        case eBuildingType::horseTrainer: {
            const auto fv = static_cast<eVendor*>(fvb);
            if(fv->provideType() != r) continue;
            return fv->peddlerResource();
        } break;
        default: break;
        }
    }
    return 0;
}
