#include "esoldieraction.h"

#include "characters/esoldier.h"
#include "engine/egameboard.h"

#include <math.h>
#include "epathdatafindtask.h"
#include "ewalkablehelpers.h"

#include "missiles/erockmissile.h"

#include "characters/esoldierbanner.h"

#include "emovetoaction.h"
#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"

eAttackTarget::eAttackTarget() :
    mC(nullptr), mB(nullptr) {}

eAttackTarget::eAttackTarget(eCharacter* const c) :
    mC(c), mB(nullptr) {}

eAttackTarget::eAttackTarget(eBuilding* const b) :
    mC(nullptr), mB(b) {}

eTile* eAttackTarget::tile() const {
    if(mC) return mC->tile();
    if(mB) return mB->centerTile();
    return nullptr;
}

bool eAttackTarget::valid() const {
    return mC || mB;
}

bool eAttackTarget::defend(const double a) {
    if(mC) return mC->defend(a);
    if(mB) return mB->defend(a);
    return true;
}

bool eAttackTarget::dead() const {
    if(mC) return mC->dead();
    if(mB) return false;
    return true;
}

void eAttackTarget::clear() {
    mC = nullptr;
    mB = nullptr;
}

bool eAttackTarget::building() const {
    return mB;
}

double eAttackTarget::absX() const {
    if(mC) return mC->absX();
    if(mB) {
        const auto t = mB->centerTile();
        if(!t) return 0.;
        return t->x();
    }
    return 0.;
}

double eAttackTarget::absY() const {
    if(mC) return mC->absY();
    if(mB) {
        const auto t = mB->centerTile();
        if(!t) return 0.;
        return t->y();
    }
    return 0.;
}

bool eSoldierAction::decide() {
    return true;
}

void signalBeingAttack(eSoldier* const attacked,
                       eSoldier* const by,
                       eGameBoard& brd) {
    const auto tt = attacked->tile();
    const int ttx = tt->x();
    const int tty = tt->y();
    for(int ii = -2; ii <= 2; ii++) {
        for(int jj = -2; jj <= 2; jj++) {
            const auto tt = brd.tile(ttx + ii, tty + jj);
            if(!tt) continue;
            const auto& ccchars = tt->characters();
            for(const auto& ccc : ccchars) {
                if(!ccc->isSoldier()) continue;
                if(ccc->playerId() != attacked->playerId()) continue;
                if(ccc->dead()) continue;

                const auto sss = static_cast<eSoldier*>(ccc.get());
                const auto aaa = sss->soldierAction();
                aaa->beingAttacked(by);
            }
        }
    }
}

void eSoldierAction::increment(const int by) {
    const int rangeAttackCheck = 500;
    const int lookForEnemyCheck = 500;
    const int missileCheck = 200;
    const int buildingCheck = 5000;

    const auto c = character();
    if(c->dead()) return;
    const auto s = static_cast<eSoldier*>(c);
    const int range = s->range();
    auto& brd = c->getBoard();
    const auto ct = c->tile();
    if(!ct) return;
    const int tx = ct->x();
    const int ty = ct->y();
    const int pid = c->playerId();

    if(mAttack) {
        const auto tt = mAttackTarget.tile();
        const int ttx = tt ? tt->x() : 0;
        const int tty = tt ? tt->y() : 0;
        const auto at = c->actionType();
        if(range > 0 && mAttackTarget.valid() &&
           at == eCharacterActionType::fight2) {
            mMissile += by;
            if(mMissile > missileCheck) {
                mMissile = mMissile - missileCheck;
                eMissile::sCreate<eRockMissile>(brd, tx, ty, 0.5,
                                                ttx, tty, 0.5, 2);
            }
        }
        mAttackTime += by;
        bool finishAttack = !mAttackTarget.valid() ||
                            mAttackTarget.dead() ||
                            (mAttackTime > 1000 && !mAttackTarget.building());
        if(mAttackTarget.valid() && !mAttackTarget.dead()) {
            const double att = by*c->attack();
            const bool d = mAttackTarget.defend(att);
            if(d) finishAttack = true;
        }
        if(finishAttack) {
            mAttack = false;
            mAttackTarget.clear();
            mAttackTime = 0;
            mRangeAttack = rangeAttackCheck;
            c->setActionType(eCharacterActionType::stand);
            setCurrentAction(nullptr);
            mLookForEnemy = lookForEnemyCheck;
        } else {
            return;
        }
    }

    mBuildingAttack += by;
    const bool buildingAttack = mBuildingAttack > buildingCheck;
    if(buildingAttack) {
        mBuildingAttack -= buildingCheck;
    }
    const vec2d cpos{c->absX(), c->absY()};
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            const auto t = brd.tile(tx + i, ty + j);
            if(!t) continue;
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(!cc->isSoldier()) continue;
                if(cc->playerId() == pid) continue;
                if(cc->dead()) continue;
                const vec2d ccpos{cc->absX(), cc->absY()};
                const vec2d posdif = ccpos - cpos;
                const double dist = posdif.length();
                if(dist > 1.) continue;
                mAttackTarget = eAttackTarget(cc.get());
                mAttack = true;
                mAttackTime = 0;
                c->setActionType(eCharacterActionType::fight);
                mAngle = posdif.angle();
                const auto o = sAngleOrientation(mAngle);
                c->setOrientation(o);
                return;
            }
            if(buildingAttack) {
                const bool r = attackBuilding(t);
                if(r) return;
            }
        }
    }

    if(range > 0) {
        mRangeAttack += by;
        if(mRangeAttack > rangeAttackCheck) {
            mRangeAttack -= rangeAttackCheck;
            for(int i = -range; i <= range; i++) {
                for(int j = -range; j <= range; j++) {
                    const auto t = brd.tile(tx + i, ty + j);
                    if(!t) continue;
                    const auto& chars = t->characters();
                    for(const auto& cc : chars) {
                        if(!cc->isSoldier()) continue;
                        if(cc->playerId() == pid) continue;
                        if(cc->dead()) continue;
                        const vec2d ccpos{cc->absX(), cc->absY()};
                        const vec2d posdif = ccpos - cpos;
                        mAttackTarget = eAttackTarget(cc.get());
                        mAttack = true;
                        mAttackTime = 0;
                        c->setActionType(eCharacterActionType::fight2);
                        mAngle = posdif.angle();
                        const auto o = sAngleOrientation(mAngle);
                        c->setOrientation(o);
                        const auto ss = static_cast<eSoldier*>(cc.get());
                        signalBeingAttack(ss, s, brd);
                        return;
                    }
                    if(buildingAttack) {
                        const bool r = attackBuilding(t);
                        if(r) {
                            c->setActionType(eCharacterActionType::fight2);
                            return;
                        }
                    }
                }
            }
        }
    }

    if(!currentAction()) {
        mLookForEnemy += by;
        if(mLookForEnemy > lookForEnemyCheck) {
            mLookForEnemy -= lookForEnemyCheck;
            const int erange = 3 + range;
            bool found = false;
            for(int i = -erange; i <= erange && !found; i++) {
                for(int j = -erange; j <= erange && !found; j++) {
                    const int ttx = tx + i;
                    const int tty = ty + j;
                    const auto t = brd.tile(ttx, tty);
                    if(!t) continue;
                    const auto& chars = t->characters();
                    for(const auto& cc : chars) {
                        if(!cc->isSoldier()) continue;
                        if(cc->playerId() == pid) continue;
                        if(cc->dead()) continue;
                        found = true;
                        goTo(ttx, tty, range);
                        break;
                    }
                }
            }
        }
    }
    if(!currentAction()) {
        goBackToBanner();
    }

    eComplexAction::increment(by);
}

void eSoldierAction::moveBy(const double dx, const double dy) {
    const auto c = character();
    const auto ct = c->tile();
    if(!ct) return;
    const int tx = ct->x();
    const int ty = ct->y();
    const double newX = tx + c->x() + dx;
    const double newY = ty + c->y() + dy;
    const int newIX = floor(newX);
    const int newIY = floor(newY);
    const auto& brd = c->getBoard();
    const auto newT = brd.tile(newIX, newIY);
    if(!newT) return;
    c->changeTile(newT);
    const double newFX = newX - newIX;
    const double newFY = newY - newIY;
    c->setX(newFX);
    c->setY(newFY);
}

std::function<bool(eTile* const)> eSoldierAction::obsticleHandler() {
    const stdptr<eSoldierAction> tptr(this);
    return [tptr, this](eTile* const tile) {
        if(!tptr) return false;
        const auto ub = tile->underBuilding();
        if(!ub) return false;
        const auto ubt = ub->type();
        const bool r = eBuilding::sWalkableBuilding(ubt);
        if(r) return false;
        attackBuilding(tile);
        return true;
    };
}

void eSoldierAction::goTo(const int fx, const int fy,
                          const int dist) {
    const auto c = character();
    const auto t = c->tile();
    const int sx = t->x();
    const int sy = t->y();
    if(abs(fx - sx) <= dist && abs(fy - sy) <= dist) return;

    const stdptr<eSoldierAction> tptr(this);
    const stdptr<eCharacter> cptr(character());

    const auto hha = [fx, fy, dist](eThreadTile* const t) {
        return abs(t->x() - fx) <= dist && abs(t->y() - fy) <= dist;
    };

    const auto finishAct = [cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::stand);
    };

    const int pid = c->playerId();
    const bool attackBuildings = pid != 1;
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    eTileWalkable pathFindWalkable =
        eWalkableObject::sCreateDefault();
    eTileWalkable moveWalkable = nullptr;
    if(attackBuildings) {
        pathFindWalkable = eWalkableHelpers::eWalkableObject::sCreateTerrain();
        moveWalkable = eWalkableObject::sCreateDefault();
    }

    const auto a = e::make_shared<eMoveToAction>(
                       cptr.get(), finishAct, finishAct);
    if(attackBuildings) {
        a->setObsticleHandler(obsticleHandler());
    }
    a->setFoundAction([tptr, cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });
    a->start(hha, pathFindWalkable, moveWalkable);
    setCurrentAction(a);
}

void eSoldierAction::goHome() {
    const auto c = character();
    const auto& brd = c->getBoard();
    const auto b = sFindHome(c->type(), brd);
    if(!b) {
        c->kill();
        return;
    }

    const stdptr<eSoldierAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto finishAct = [cptr]() {
        if(!cptr) return;
        cptr->kill();
    };

    const auto a = e::make_shared<eMoveToAction>(
                       cptr.get(), finishAct, finishAct);
    a->setFoundAction([tptr, cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });
    a->setFindFailAction(finishAct);
    a->start(b, eWalkableObject::sCreateDefault());
    setCurrentAction(a);
}

void eSoldierAction::beingAttacked(eSoldier* const ss) {
    const auto tt = ss->tile();
    const int ttx = tt->x();
    const int tty = tt->y();
    beingAttacked(ttx, tty);
}

void eSoldierAction::beingAttacked(const int ttx, const int tty) {
    if(mAttack) return;
    if(currentAction()) return;
    goTo(ttx, tty);
}

eBuilding* eSoldierAction::sFindHome(const eCharacterType t,
                                     const eGameBoard& brd) {
    eGameBoard::eBuildingValidator v;
    if(t == eCharacterType::rockThrower) {
        v = [](eBuilding* const b) {
            const auto bt = b->type();
            if(bt != eBuildingType::commonHouse) return false;
            const auto ch = static_cast<eSmallHouse*>(b);
            if(ch->level() < 2) return false;
            return true;
        };
    } else if(t == eCharacterType::hoplite) {
        v = [](eBuilding* const b) {
            const auto bt = b->type();
            if(bt != eBuildingType::eliteHousing) return false;
            const auto eh = static_cast<eEliteHousing*>(b);
            if(eh->level() < 2) return false;
            return true;
        };
    } else { // horseman
        v = [](eBuilding* const b) {
            const auto bt = b->type();
            if(bt != eBuildingType::eliteHousing) return false;
            const auto eh = static_cast<eEliteHousing*>(b);
            if(eh->level() < 4) return false;
            return true;
        };
    }
    const auto b = brd.randomBuilding(v);
    return b;
}

bool eSoldierAction::attackBuilding(eTile* const t) {
    const auto ub = t->underBuilding();
    if(!ub) return false;
    const auto c = character();
    const int pid = c->playerId();
    const vec2d cpos{c->absX(), c->absY()};
    if(ub->playerId() == pid) return false;
    const bool att = eBuilding::sAttackable(ub->type());
    if(!att) return false;
    mAttackTarget = eAttackTarget(ub);
    mAttack = true;
    mAttackTime = 0;
    c->setActionType(eCharacterActionType::fight);
    const vec2d ccpos{1.*t->x(), 1.*t->y()};
    const vec2d posdif = ccpos - cpos;
    mAngle = posdif.angle();
    const auto o = sAngleOrientation(mAngle);
    c->setOrientation(o);
    return true;
}

void eSoldierAction::goBackToBanner() {
    const auto c = character();
    const auto s = static_cast<eSoldier*>(c);
    const auto b = s->banner();
    if(!b) return;

    const auto ct = c->tile();
    const auto tt = b->place(s);
    if(!tt) return;
    if(ct == tt) {
        setCurrentAction(nullptr);
        c->setActionType(eCharacterActionType::stand);
        return;
    }

    const int ttx = tt->x();
    const int tty = tt->y();
    goTo(ttx, tty);
}
