#include "esoldierbanner.h"

#include <algorithm>

#include "engine/etile.h"
#include "engine/egameboard.h"
#include "characters/esoldier.h"
#include "characters/erockthrower.h"
#include "characters/ehoplite.h"
#include "characters/ehorseman.h"
#include "characters/actions/esoldieraction.h"
#include "eiteratesquare.h"

#include "evectorhelpers.h"
#include "ewalkablehelpers.h"

int gNextId = 0;

eSoldierBanner::eSoldierBanner(const eBannerType type,
                               eGameBoard& board) :
    eObject(board),
    mType(type), mId(gNextId++), mBoard(board) {}

void eSoldierBanner::moveTo(const int x, const int y) {
    if(mX == x && mY == y) return;

    if(mPlayerId == 1 && mTile) {
        mTile->setSoldierBanner(nullptr);
    }
    const auto t = mBoard.tile(x, y);
    if(mPlayerId == 1 && t) {
        t->setSoldierBanner(this);
    }
    mTile = t;

    mX = x;
    mY = y;

    updatePlaces();
    callSoldiers();
}

void eSoldierBanner::goHome() {
    if(mHome) return;
    mHome = true;
    const auto soldiers = notDead();
    for(const auto s : soldiers) {
        const auto a = s->soldierAction();
        a->goHome();
    }
}

void eSoldierBanner::backFromHome() {
    if(!mHome) return;
    mHome = false;
    const auto soldiers = notDead();
    for(const auto s : soldiers) {
        const auto a = s->soldierAction();
        a->goBackToBanner();
    }
    updateCount();
}

void eSoldierBanner::callSoldiers() {
    const auto soldiers = notDead();
    if(soldiers.empty()) return;

    for(const auto s : soldiers) {
        const auto tt = mPlaces[s];

        const int ttx = tt->x();
        const int tty = tt->y();

        const auto a = s->soldierAction();
        a->goTo(ttx, tty);
    }
}

void eSoldierBanner::addSoldier(eSoldier* const s) {
    mSoldiers.push_back(s);
    updatePlaces();
}

void eSoldierBanner::removeSoldier(eSoldier* const s) {
    mPlaces.erase(s);
    const bool r = eVectorHelpers::remove(mSoldiers, s);
    if(r) updatePlaces();
}

eTile* eSoldierBanner::place(eSoldier* const s) const {
    const auto it = mPlaces.find(s);
    if(it == mPlaces.end()) return nullptr;
    return it->second;
}

void eSoldierBanner::killAll() {
    for(const auto s : mSoldiers) {
        s->kill();
    }
    mSoldiers.clear();
}

void eSoldierBanner::incCount() {
    mCount++;
    updateCount();
}

void eSoldierBanner::decCount() {
    mCount--;
    updateCount();
}

bool eSoldierBanner::stationary() const {
    for(const auto s : mSoldiers) {
        const auto at = s->actionType();
        if(at != eCharacterActionType::stand) return false;
    }
    return true;
}

void eSoldierBanner::sPlace(const std::vector<eSoldierBanner*>& bs,
                            const int ctx, const int cty,
                            eGameBoard& board, const int dist) {

    int isld = 0;
    const int slds = bs.size();

    const auto prcsTile = [&](const int i, const int j) {
        if(isld >= slds) return false;
        const int tx = ctx + i;
        const int ty = cty + j;
        const auto tt = board.tile(tx, ty);
        if(!tt) return false;
        if(!tt->walkable()) return false;
        if(tt->soldierBanner()) return false;

        const auto s = bs[isld++];
        s->moveTo(tx, ty);
        return false;
    };

    const int kinc = slds == 1 ? 1 : dist;
    for(int k = 0; isld < slds; k += kinc) {
        eIterateSquare::iterateSquare(k, prcsTile, dist);
    }
}

void eSoldierBanner::updatePlaces() {
    const auto soldiers = notDead();
    if(soldiers.empty()) return;

    int isld = 0;
    const int slds = soldiers.size();

    const auto prcsTile = [&](const int i, const int j) {
        if(isld >= slds) return false;
        const auto tt = mBoard.tile(mX + i, mY + j);
        if(!tt) return false;
        if(mPlayerId == 1) {
            if(!eWalkableHelpers::sDefaultWalkable(tt)) return false;
        } else {
            if(!eWalkableHelpers::sBuildingsWalkable(tt)) return false;
        }

        const auto s = soldiers[isld++];
        mPlaces[s] = tt;
        return false;
    };

    for(int k = 0; isld < slds; k++) {
        eIterateSquare::iterateSquare(k, prcsTile);
    }
}

void eSoldierBanner::updateCount() {
    if(mHome) return;
    auto soldiers = notDead();
    const int n = soldiers.size();
    for(int i = n; i < mCount; i++) {
        eCharacterType cht;
        switch(mType) {
        case eBannerType::rockThrower:
            cht = eCharacterType::rockThrower;
            break;
        case eBannerType::hoplite:
            cht = eCharacterType::hoplite;
            break;
        case eBannerType::horseman:
            cht = eCharacterType::horseman;
            break;
        }
        const auto home = eSoldierAction::sFindHome(cht, mBoard);
        if(!home) break;
        stdsptr<eSoldier> h;
        switch(mType) {
        case eBannerType::rockThrower:
            h = e::make_shared<eRockThrower>(mBoard);
            break;
        case eBannerType::hoplite:
            h = e::make_shared<eHoplite>(mBoard);
            break;
        case eBannerType::horseman:
            h = e::make_shared<eHorseman>(mBoard);
            break;
        }
        h->setBanner(this);
        const auto a = e::make_shared<eSoldierAction>(h.get(), [](){}, [](){});
        h->setSoldierAction(a);
        h->setAction(a);
        h->changeTile(home->centerTile());
        h->setActionType(eCharacterActionType::stand);
        a->goBackToBanner();
    }

    for(int i = mCount; i < n; i++) {
        const auto s = soldiers.back();
        soldiers.pop_back();
        const auto a = s->soldierAction();
        a->goHome();
        s->setBanner(nullptr);
    }
    updatePlaces();
}

std::vector<eSoldier*> eSoldierBanner::notDead() const {
    std::vector<eSoldier*> soldiers;
    soldiers.reserve(mSoldiers.size());
    for(const auto s : mSoldiers) {
        if(s->dead()) continue;
        soldiers.push_back(s);
    }
    return soldiers;
}
