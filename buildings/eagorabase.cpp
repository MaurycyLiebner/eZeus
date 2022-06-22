#include "eagorabase.h"

#include "eagoraspace.h"
#include "ebuildingrenderer.h"
#include "engine/egameboard.h"

eAgoraBase::eAgoraBase(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int nPts) :
    eBuilding(board, type, sw, sh),
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
    eBuilding::erase();
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
