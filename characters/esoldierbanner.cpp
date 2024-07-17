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

#include "eiteratesquare.h"
#include "engine/epathfinder.h"

#include "elanguage.h"
#include "estringhelpers.h"

int gNextId = 0;

eSoldierBanner::eSoldierBanner(const eBannerType type,
                               eGameBoard& board) :
    eObject(board),
    mType(type), mId(gNextId++), mBoard(board) {
    mBoard.registerAllSoldierBanner(this);
    const int nameId = mId % 30;
    auto name = eLanguage::zeusText(138, nameId);
    eStringHelpers::replaceAll(name, "&quot;", "\"");
    setName(name);
}

eSoldierBanner::~eSoldierBanner() {
    mBoard.unregisterAllSoldierBanner(this);
}

eCharacterType eSoldierBanner::characterType() const {
    const bool p = mBoard.poseidonMode();
    if(p) {
        switch(mType) {
        case eBannerType::hoplite:
            return eCharacterType::hoplitePoseidon;
        case eBannerType::horseman:
            return eCharacterType::chariotPoseidon;
        case eBannerType::rockThrower:
            return eCharacterType::archerPoseidon;
        case eBannerType::amazon:
            return eCharacterType::amazon;
        case eBannerType::aresWarrior:
            return eCharacterType::aresWarrior;
        case eBannerType::enemy:
            return eCharacterType::none;
        }
    } else {
        switch(mType) {
        case eBannerType::hoplite:
            return eCharacterType::hoplite;
        case eBannerType::horseman:
            return eCharacterType::horseman;
        case eBannerType::rockThrower:
            return eCharacterType::rockThrower;
        case eBannerType::amazon:
            return eCharacterType::amazon;
        case eBannerType::aresWarrior:
            return eCharacterType::aresWarrior;
        case eBannerType::enemy:
            return eCharacterType::none;
        }
    }
    return eCharacterType::none;
}

stdsptr<eSoldier> eSoldierBanner::createSoldier(eTile* const t) {
    const auto ct = characterType();
    const auto c = eCharacter::sCreate(ct, mBoard);
    const auto s = c->ref<eSoldier>();;
    s->setBanner(this);
    const auto a = e::make_shared<eSoldierAction>(s.get());
    c->setAction(a);
    c->changeTile(t);
    c->setActionType(eCharacterActionType::stand);
    if(mHome) a->goHome();
    else a->goBackToBanner();
    return s;
}

void eSoldierBanner::moveTo(const int x, const int y) {
    const auto t = mBoard.tile(x, y);
    if(!t || t == mTile) return;

    if(mPlayerId == 1 && mTile) {
        mTile->setSoldierBanner(nullptr);
    }
    if(mPlayerId == 1 && t) {
        t->setSoldierBanner(this);
    }
    mTile = t;

    updatePlaces();
    if(!mHome) callSoldiers();
}

void eSoldierBanner::moveToDefault() {
    if(mPlayerId != 1) return;
    switch(mType) {
    case eBannerType::rockThrower:
    case eBannerType::hoplite:
    case eBannerType::horseman: {
        const auto palace = mBoard.palace();
        if(!palace) return;
        const auto ts = palace->tiles();
        for(const auto t : ts) {
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
        for(const auto t : ts) {
            const auto bb = t->soldierBanner();
            if(bb) continue;
            moveTo(t->x(), t->y());
            break;
        }
    } break;
    case eBannerType::enemy:
        break;
    }
}

void eSoldierBanner::goHome() {
    if(mMilitaryAid) return;
    if(mPlayerId != 1) return;
    if(mHome) return;
    mHome = true;
    for(const auto s : mSoldiers) {
        if(s->dead()) continue;
        const auto a = s->soldierAction();
        if(a) a->goHome();
    }
}

void eSoldierBanner::goAbroad() {
    if(mAbroad) return;
    if(mSelected) mBoard.deselectBanner(this);
    if(mHome) backFromHome();
    mAbroad = true;
    for(const auto s : mSoldiers) {
        if(s->dead()) continue;
        const auto a = s->soldierAction();
        if(a) a->goAbroad();
    }
    if(mTile) {
        mTile->setSoldierBanner(nullptr);
        mTile = nullptr;
    }
}

void eSoldierBanner::backFromAbroad(int& wait) {
    if(!mAbroad) return;
    mAbroad = false;
    moveToDefault();
    const auto entryPoint = mBoard.entryPoint();
    if(entryPoint) {
        while((int)mSoldiers.size() < mCount) {
            const auto s = createSoldier(entryPoint);
            const auto a = s->soldierAction();
            if(!a) continue;
            a->waitAndGoHome(wait);
            wait += 150;
        }
        mHome = true;
    } else {
        goHome();
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

bool eSoldierBanner::isGoingHome() const {
    if(!mHome) return false;
    return !mSoldiers.empty();
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

bool eSoldierBanner::fighting() const {
    for(const auto s : mSoldiers) {
        const auto at = s->actionType();
        if(at == eCharacterActionType::fight ||
           at == eCharacterActionType::fight2) return true;
    }
    return false;
}

void eSoldierBanner::read(eReadStream& src) {
    src >> mIOID;
    src >> mMilitaryAid;
    src >> mHome;
    src >> mAbroad;
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
    dst << mIOID;
    dst << mMilitaryAid;
    dst << mHome;
    dst << mAbroad;
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
                            eGameBoard& board, const int dist,
                            const int minDistFromEdge) {
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

    const int bw = board.width();
    const int bh = board.height();

    const auto prcsTile = [&](const int i, const int j) {
        if(isld >= slds) return false;
        const int tx = ctx + i;
        const int ty = cty + j;
        const auto tt = board.tile(tx, ty);
        if(!tt) return false;
        const int dtx = tt->dx();
        const int dty = tt->dy();
        if(dtx < minDistFromEdge) return false;
        if(dty < 2*minDistFromEdge) return false;
        if(dtx > bw - minDistFromEdge) return false;
        if(dty > bh - 2*minDistFromEdge) return false;
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

std::string eSoldierBanner::sName(
        const eBannerType type,
        const bool atlantean) {
    if(atlantean) {
        switch(type) {
        case eBannerType::hoplite:
            return eLanguage::zeusText(138, 79);
            break;
        case eBannerType::rockThrower:
            return eLanguage::zeusText(138, 77);
            break;
        case eBannerType::horseman:
            return eLanguage::zeusText(138, 80);
            break;
        default:
            break;
        }
    } else {
        switch(type) {
        case eBannerType::hoplite:
            return eLanguage::zeusText(138, 72);
            break;
        case eBannerType::rockThrower:
            return eLanguage::zeusText(138, 74);
            break;
        case eBannerType::horseman:
            return eLanguage::zeusText(138, 71);
            break;
        default:
            break;
        }
    }
    return "";
}

void eSoldierBanner::updatePlaces() {
    if(!mTile) return;
    const auto soldiers = notDead();
    if(soldiers.empty()) return;

    int isld = 0;
    const int slds = soldiers.size();

    const auto prcsTile = [&](const int i, const int j) {
        if(isld >= slds) return false;
        if(!mTile) return false;
        const int tx = mTile->x();
        const int ty = mTile->y();
        const auto tt = mBoard.tile(tx + i, ty + j);
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
    if(mMilitaryAid) return;
    if(mPlayerId != 1) return;
    auto soldiers = notDead();
    const int n = soldiers.size();
    if(!mHome && !mAbroad) {
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
            case eBannerType::enemy:
                return;
            }
            const auto home = eSoldierAction::sFindHome(cht, mBoard);
            if(!home) break;
            createSoldier(home->centerTile());
        }

        for(int i = mCount; i < n; i++) {
            const auto s = soldiers.back();
            soldiers.pop_back();
            const auto a = s->soldierAction();
            if(a) a->goHome();
            s->setBanner(nullptr);
        }
    }
    const auto tptr = ref<eSoldierBanner>();
    if(mCount <= 0 && soldiers.size() == 0) {
        switch(mType) {
        case eBannerType::rockThrower:
        case eBannerType::hoplite:
        case eBannerType::horseman:
            mBoard.unregisterSoldierBanner(tptr);
            break;
        case eBannerType::amazon:
        case eBannerType::aresWarrior:
            break;
        case eBannerType::enemy:
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
