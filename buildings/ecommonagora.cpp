#include "ecommonagora.h"

#include "eagoraspace.h"
#include "ebuildingrenderer.h"
#include "engine/egameboard.h"

int sw(const eAgoraOrientation o) {
    switch(o) {
    case eAgoraOrientation::bottomLeft:
    case eAgoraOrientation::topRight:
        return 6;
    case eAgoraOrientation::bottomRight:
    case eAgoraOrientation::topLeft:
        return 3;
    }
}

int sh(const eAgoraOrientation o) {
    switch(o) {
    case eAgoraOrientation::bottomLeft:
    case eAgoraOrientation::topRight:
        return 3;
    case eAgoraOrientation::bottomRight:
    case eAgoraOrientation::topLeft:
        return 6;
    }
}

eCommonAgora::eCommonAgora(const eAgoraOrientation o, eGameBoard& board) :
    eBuilding(board, eBuildingType::commonAgora, sw(o), sh(o)),
    mO(o) {
    for(int i = 0; i < nPts(); i++) {
        mBs.push_back(nullptr);
    }
}

SDL_Point eCommonAgora::pt(const int id) const {
    const auto rect = tileRect();
    const int rx = rect.x;
    const int ry = rect.y;
    int dx;
    int dy;
    int ddx;
    int ddy;
    switch(mO) {
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

eBuilding* eCommonAgora::building(const int id) const {
    return mBs[id].get();
}

void eCommonAgora::setBuilding(const int id, const stdsptr<eBuilding>& b) {
    mBs[id] = b;

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

void eCommonAgora::fillSpaces() {
    auto& brd = getBoard();
    for(int i = 0; i < nPts(); i++) {
        const auto b = building(i);
        if(b) continue;
        const auto space = e::make_shared<eAgoraSpace>(brd);
        setBuilding(i, space);
    }
}
