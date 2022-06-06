#include "esoldierbanner.h"

#include <algorithm>

#include "engine/etile.h"
#include "engine/egameboard.h"
#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"
#include "eiteratesquare.h"

eSoldierBanner::eSoldierBanner(const eBannerType type,
                               const int id, eGameBoard& board) :
    mType(type), mId(id), mBoard(board) {

}

void eSoldierBanner::moveTo(const int x, const int y) {
    if(mX == x && mY == y) return;

    if(mTile) {
        mTile->setBanner(nullptr);
    }
    const auto t = mBoard.tile(x, y);
    if(t) {
        t->setBanner(this);
    }
    mTile = t;

    mX = x;
    mY = y;

    callSoldiers();
}


void eSoldierBanner::callSoldiers() {
    std::vector<eSoldier*> soldiers;
    soldiers.reserve(mSoldiers.size());
    for(const auto& s : mSoldiers) {
        if(s->dead()) continue;
        soldiers.push_back(s);
    }

    if(soldiers.empty()) return;

    int isld = 0;
    const int slds = soldiers.size();

    const auto prcsTile = [&](const int i, const int j) {
        if(isld >= slds) return;
        const auto tt = mBoard.tile(mX + i, mY + j);
        if(!tt) return;
        if(!tt->walkable()) return;

        const auto s = soldiers[isld++];
        mPlaces[s] = tt;
        const auto t = s->tile();
        const int tx = t->x();
        const int ty = t->y();

        const int ttx = tt->x();
        const int tty = tt->y();

        const auto a = s->soldierAction();
        a->setPathForce(tx, ty, ttx, tty);
    };

    for(int k = 0; isld < slds; k++) {
        eIterateSquare::iterateSquare(k, prcsTile);
    }
}

void eSoldierBanner::addSoldier(eSoldier* const s) {
    mSoldiers.push_back(s);
}

void eSoldierBanner::removeSoldier(eSoldier* const s) {
    mPlaces.erase(s);
    const auto it = std::find(mSoldiers.begin(), mSoldiers.end(), s);
    if(it == mSoldiers.end()) return;
    mSoldiers.erase(it);
}

eTile* eSoldierBanner::place(eSoldier* const s) {
    const auto it = mPlaces.find(s);
    if(it == mPlaces.end()) return nullptr;
    return it->second;
}
