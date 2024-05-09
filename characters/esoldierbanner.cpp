#include "esoldierbanner.h"

#include <algorithm>

#include "engine/etile.h"
#include "engine/egameboard.h"
#include "characters/esoldier.h"
#include "characters/erockthrower.h"
#include "characters/ehoplite.h"
#include "characters/ehorseman.h"
#include "characters/eamazon.h"
#include "characters/eareswarrior.h"
#include "characters/actions/esoldieraction.h"
#include "eiteratesquare.h"

#include "evectorhelpers.h"
#include "ewalkablehelpers.h"

#include "buildings/epalace.h"
#include "buildings/epalacetile.h"

#include "elanguage.h"

int gNextId = 0;

eSoldierBanner::eSoldierBanner(const eBannerType type,
                               eGameBoard& board) :
    eObject(board),
    mType(type), mId(gNextId++), mBoard(board) {
    const int nameId = mId % 20;
    const auto nameIdStr = std::to_string(nameId);
    const auto namet = "soldier_banner_name_" + nameIdStr;
    setName(eLanguage::text(namet));
}

void eSoldierBanner::moveTo(const int x, const int y) {
    if(mX == x && mY == y) return;
    const auto t = mBoard.tile(x, y);
    if(!t) return;


    if(mPlayerId == 1 && mTile) {
        mTile->setSoldierBanner(nullptr);
    }
    if(mPlayerId == 1 && t) {
        t->setSoldierBanner(this);
    }
    mTile = t;

    mX = x;
    mY = y;

    updatePlaces();
    callSoldiers();
}

void eSoldierBanner::moveToDefault() {
    switch(mType) {
    case eBannerType::rockThrower:
    case eBannerType::hoplite:
    case eBannerType::horseman: {
        const auto palace = mBoard.palace();
        if(!palace) return;
        const auto ts = palace->tiles();
        for(const auto& t : ts) {
            if(t->other()) continue;
            const auto tt = t->centerTile();
            if(!tt) continue;
            const auto bb = tt->soldierBanner();
            if(bb) continue;
            moveTo(tt->x(), tt->y());
            break;
        }
    } break;
    case eBannerType::amazon:
    case eBannerType::aresWarrior: {
        const auto s = mType == eBannerType::amazon ?
                            mBoard.sanctuary(eGodType::artemis) :
                            mBoard.sanctuary(eGodType::ares);
        if(!s) return;
        const auto ts = s->warriorTiles();
        for(const auto& t : ts) {
            const auto bb = t->soldierBanner();
            if(bb) continue;
            moveTo(t->x(), t->y());
            break;
        }
    } break;
    }
}

void eSoldierBanner::goHome() {
    if(mHome) return;
    mHome = true;
    for(const auto s : mSoldiers) {
        if(s->dead()) continue;
        const auto a = s->soldierAction();
        if(a) a->goHome();
    }
}

void eSoldierBanner::backFromHome() {
    if(!mHome) return;
    mHome = false;
    for(const auto s : mSoldiers) {
        if(s->dead()) continue;
        const auto a = s->soldierAction();
        if(a) a->goBackToBanner();
    }
    updateCount();
}

void eSoldierBanner::callSoldiers() {
    for(const auto s : mSoldiers) {
        if(s->dead()) continue;
        const auto tt = mPlaces[s];

        const int ttx = tt->x();
        const int tty = tt->y();

        const auto a = s->soldierAction();
        if(a) a->goTo(ttx, tty);
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

void eSoldierBanner::killAllWithCorpse() {
    for(const auto s : mSoldiers) {
        s->killWithCorpse();
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

void eSoldierBanner::read(eReadStream& src) {
    src >> mHome;
    src >> mX;
    src >> mY;
    mTile = src.readTile(mBoard);
    if(mPlayerId == 1 && mTile) {
        mTile->setSoldierBanner(this);
    }
    src >> mCount;
    src >> mPlayerId;

    int np;
    src >> np;
    for(int i = 0; i < np; i++) {
        const auto t = src.readTile(mBoard);
        src.readCharacter(&mBoard, [this, t](eCharacter* const c) {
            const auto s = static_cast<eSoldier*>(c);
            mPlaces[s] = t;
        });
    }

    int ns;
    src >> ns;
    for(int i = 0; i < ns; i++) {
        src.readCharacter(&mBoard, [this](eCharacter* const c) {
            const auto s = static_cast<eSoldier*>(c);
            mSoldiers.push_back(s);
        });
    }
}

void eSoldierBanner::write(eWriteStream& dst) const {
    dst << mHome;
    dst << mX;
    dst << mY;
    dst.writeTile(mTile);
    dst << mCount;
    dst << mPlayerId;

    dst << mPlaces.size();
    for(const auto& p : mPlaces) {
        dst.writeTile(p.second);
        dst.writeCharacter(p.first);
    }

    dst << mSoldiers.size();
    for(const auto s : mSoldiers) {
        dst.writeCharacter(s);
    }
}

void eSoldierBanner::sPlace(std::vector<eSoldierBanner*> bs,
                            const int ctx, const int cty,
                            eGameBoard& board, const int dist) {
    if(bs.empty()) return;
    const auto tt = board.tile(ctx, cty);
    if(tt) {
        const auto b = tt->underBuilding();
        if(b) {
            const auto bt = b->type();
            if(bt == eBuildingType::palace ||
               bt == eBuildingType::palaceTile) {
                for(const auto bb : bs) {
                    const auto bbt = bb->type();
                    if(bbt == eBannerType::hoplite ||
                       bbt == eBannerType::rockThrower ||
                       bbt == eBannerType::horseman) {
                        bb->moveToDefault();
                        eVectorHelpers::remove(bs, bb);
                    }
                }
            } else if(const auto sb = dynamic_cast<eSanctBuilding*>(b)) {
                const auto s = sb->sanctuary();
                const auto gt = s->godType();
                for(const auto bb : bs) {
                    const auto bbt = bb->type();
                    if((bbt == eBannerType::amazon && gt == eGodType::artemis) ||
                       (bbt == eBannerType::aresWarrior && gt == eGodType::ares)) {
                        bb->moveToDefault();
                        eVectorHelpers::remove(bs, bb);
                    }
                }
            }
        }
    }

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
        (void)isld;
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
        (void)isld;
        eIterateSquare::iterateSquare(k, prcsTile);
    }
}

void eSoldierBanner::updateCount() {
    auto soldiers = notDead();
    const int n = soldiers.size();
    if(!mHome) {
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
            case eBannerType::amazon:
                cht = eCharacterType::amazon;
                break;
            case eBannerType::aresWarrior:
                cht = eCharacterType::aresWarrior;
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
            case eBannerType::amazon:
                h = e::make_shared<eAmazon>(mBoard);
                break;
            case eBannerType::aresWarrior:
                h = e::make_shared<eAresWarrior>(mBoard);
                break;
            }
            h->setBanner(this);
            const auto a = e::make_shared<eSoldierAction>(h.get());
            h->setAction(a);
            h->changeTile(home->centerTile());
            h->setActionType(eCharacterActionType::stand);
            a->goBackToBanner();
        }

        for(int i = mCount; i < n; i++) {
            const auto s = soldiers.back();
            soldiers.pop_back();
            const auto a = s->soldierAction();
            if(a) a->goHome();
            s->setBanner(nullptr);
        }
    }
    if(mCount <= 0 && soldiers.size() == 0) {
        switch(mType) {
        case eBannerType::rockThrower:
        case eBannerType::hoplite:
        case eBannerType::horseman:
            mBoard.unregisterSoldierBanner(ref<eSoldierBanner>());
            break;
        case eBannerType::amazon:
        case eBannerType::aresWarrior:
            break;
        }
        return;
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
