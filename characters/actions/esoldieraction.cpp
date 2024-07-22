#include "esoldieraction.h"

#include "characters/esoldier.h"
#include "engine/egameboard.h"

#include <math.h>

#include "missiles/erockmissile.h"
#include "missiles/earrowmissile.h"
#include "missiles/espearmissile.h"

#include "characters/esoldierbanner.h"

#include "emovetoaction.h"
#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "buildings/sanctuaries/etemplebuilding.h"
#include "ekillcharacterfinishfail.h"
#include "ewaitaction.h"

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

eSoldierAction::eSoldierAction(eCharacter* const c) :
    eComplexAction(c, eCharActionType::soldierAction) {}

bool eSoldierAction::decide() {
    return true;
}

void eSoldierAction::sSignalBeingAttack(
        eSoldier* const attacked,
        eCharacter* const by,
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
                if(aaa) aaa->beingAttacked(by);
            }
        }
    }
}

void eSoldierAction::increment(const int by) {
    if(mSpreadPeriod && currentAction()) {
        return eComplexAction::increment(by);
    } else {
        mSpreadPeriod = false;
    }
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
        const auto at = c->actionType();
        if(range > 0 && mAttackTarget.valid() &&
           at == eCharacterActionType::fight2) {
            mMissile += by;
            if(mMissile > missileCheck) {
                mMissile = mMissile - missileCheck;
                const auto tt = mAttackTarget.tile();
                const int ttx = tt ? tt->x() : 0;
                const int tty = tt ? tt->y() : 0;
                const auto ct = c->type();
                if(ct == eCharacterType::amazon ||
                   ct == eCharacterType::centaurArcher ||
                   ct == eCharacterType::egyptianArcher ||
                   ct == eCharacterType::atlanteanArcher ||
                   ct == eCharacterType::phoenicianArcher ||
                   ct == eCharacterType::persianArcher) {
                    eMissile::sCreate<eArrowMissile>(brd, tx, ty, 0.5,
                                                     ttx, tty, 0.5, 2);
                } else if(ct == eCharacterType::trojanSpearthrower ||
                          ct == eCharacterType::oceanidSpearthrower) {
                    eMissile::sCreate<eSpearMissile>(brd, tx, ty, 0.5,
                                                     ttx, tty, 0.5, 2);
                } else {
                    eMissile::sCreate<eRockMissile>(brd, tx, ty, 0.5,
                                                    ttx, tty, 0.5, 2);
                }
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
            c->setPlayFightSound(false);
            mLookForEnemy = lookForEnemyCheck;
        } else {
            return;
        }
    }
    const vec2d cpos{c->absX(), c->absY()};

    const auto setMeleeAttackTarget = [&](const stdsptr<eCharacter>& cc) {
        const vec2d ccpos{cc->absX(), cc->absY()};
        const vec2d posdif = ccpos - cpos;
        mAttackTarget = eAttackTarget(cc.get());
        mAttack = true;
        c->setPlayFightSound(true);
        mAttackTime = 0;
        c->setActionType(eCharacterActionType::fight);
        mAngle = posdif.angle();
        const auto o = sAngleOrientation(mAngle);
        c->setOrientation(o);
    };

    mBuildingAttack += by;
    const bool buildingAttack = mBuildingAttack > buildingCheck;
    if(buildingAttack) {
        mBuildingAttack -= buildingCheck;
    }
    stdsptr<eCharacter> immortal;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            const auto t = brd.tile(tx + i, ty + j);
            if(!t) continue;
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(cc->playerId() == pid) continue;
                if(cc->dead()) continue;
                const vec2d ccpos{cc->absX(), cc->absY()};
                const vec2d posdif = ccpos - cpos;
                const double dist = posdif.length();
                if(dist > 1.) continue;
                if(!cc->isSoldier()) {
                    if(cc->isImmortal()) {
                        immortal = cc;
                    }
                    continue;
                }
                setMeleeAttackTarget(cc);
                return;
            }
            if(buildingAttack) {
                const bool r = attackBuilding(t);
                if(r) {
                    c->setActionType(eCharacterActionType::fight);
                    return;
                }
            }
        }
    }
    if(immortal) {
        setMeleeAttackTarget(immortal);
        return;
    }

    const auto setRangeAttackTarget = [&](const stdsptr<eCharacter>& cc) {
        const vec2d ccpos{cc->absX(), cc->absY()};
        const vec2d posdif = ccpos - cpos;
        mAttackTarget = eAttackTarget(cc.get());
        mAttack = true;
        c->setPlayFightSound(true);
        mAttackTime = 0;
        c->setActionType(eCharacterActionType::fight2);
        mAngle = posdif.angle();
        const auto o = sAngleOrientation(mAngle);
        c->setOrientation(o);
    };

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
                        if(cc->playerId() == pid) continue;
                        if(cc->dead()) continue;
                        if(!cc->isSoldier()) {
                            if(cc->isImmortal()) {
                                immortal = cc;
                            }
                            continue;
                        }
                        setRangeAttackTarget(cc);
                        const auto ss = static_cast<eSoldier*>(cc.get());
                        sSignalBeingAttack(ss, s, brd);
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

        if(immortal) {
            setRangeAttackTarget(immortal);
            return;
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
        mGoToBannerCountdown -= by;
        if(mGoToBannerCountdown < 0) {
            mGoToBannerCountdown = 1000;
            const stdptr<eSoldierAction> tptr(this);
            const auto taskFinished = [tptr]() {
                if(!tptr) return;
                tptr->mGoToBannerCountdown = 500;
            };
            const auto taskFindFailed = [tptr]() {
                if(!tptr) return;
                tptr->mGoToBannerCountdown = 5000;
            };
            goBackToBanner(taskFindFailed, taskFinished);
        }
    }

    eComplexAction::increment(by);
}

void eSoldierAction::read(eReadStream& src) {
    eComplexAction::read(src);
    src >> mAngle;
    src >> mMissile;
    src >> mRangeAttack;
    src >> mBuildingAttack;
    src >> mLookForEnemy;
    src >> mAttackTime;
    src >> mAttack;
    mAttackTarget.read(board(), src);
    src >> mSpreadPeriod;
}

void eSoldierAction::write(eWriteStream& dst) const {
    eComplexAction::write(dst);
    dst << mAngle;
    dst << mMissile;
    dst << mRangeAttack;
    dst << mBuildingAttack;
    dst << mLookForEnemy;
    dst << mAttackTime;
    dst << mAttack;
    mAttackTarget.write(dst);
    dst << mSpreadPeriod;
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

stdsptr<eObsticleHandler> eSoldierAction::obsticleHandler() {
    return std::make_shared<eSoldierObsticleHandler>(
                board(), this);
}

void eSoldierAction::goTo(const int fx, const int fy,
                          const int dist,
                          const eAction& findFailAct,
                          const eAction& findFinishAct) {
    const auto c = character();
    const auto t = c->tile();
    const int sx = t->x();
    const int sy = t->y();
    if(abs(fx - sx) <= dist && abs(fy - sy) <= dist) return;

    const auto hha = [fx, fy, dist](eThreadTile* const t) {
        return abs(t->x() - fx) <= dist && abs(t->y() - fy) <= dist;
    };

    const auto finishAct = std::make_shared<eSA_goToFinish>(
                               board(), c);

    const int pid = c->playerId();
    const bool attackBuildings = pid != 1;
    stdsptr<eWalkableObject> pathFindWalkable =
        eWalkableObject::sCreateDefault();
    stdsptr<eWalkableObject> moveWalkable = nullptr;
    if(attackBuildings) {
        pathFindWalkable = eWalkableObject::sCreateTerrain();
        moveWalkable = eWalkableObject::sCreateDefault();
    }

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(finishAct);
    a->setFinishAction(finishAct);
    a->setFindFailAction(findFailAct);
    if(attackBuildings) {
        a->setObsticleHandler(obsticleHandler());
    }

    const stdptr<eCharacter> cptr(character());
    const stdptr<eSoldierAction> tptr(this);
    a->setFoundAction([cptr, tptr, findFinishAct]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
        if(!tptr) return;
        if(findFinishAct) findFinishAct();
    });
    a->start(hha, pathFindWalkable, moveWalkable,
             [fx, fy](eThreadBoard& board) {
        return board.tile(fx, fy);
    });
    setCurrentAction(a);
}

void eSoldierAction::waitAndGoHome(const int w) {
    const auto c = character();
    c->setActionType(eCharacterActionType::none);
    const auto finish = std::make_shared<eSA_waitAndGoHomeFinish>(
                            board(), this);
    const auto a = e::make_shared<eWaitAction>(c);
    a->setFinishAction(finish);
    a->setTime(w);
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
    const auto finishAct = std::make_shared<eSA_goHomeFinish>(
                               board(), c);

    const auto a = e::make_shared<eMoveToAction>(cptr.get());
    a->setFailAction(finishAct);
    a->setFinishAction(finishAct);
    a->setFoundAction([tptr, cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });
    a->start(b, eWalkableObject::sCreateDefault());
    setCurrentAction(a);
}

void eSoldierAction::goAbroad() {
    const auto c = character();
    auto& board = eSoldierAction::board();
    const auto hero = static_cast<eCharacter*>(c);
    const stdptr<eCharacter> cptr(hero);
    const auto fail = std::make_shared<eKillCharacterFinishFail>(
                          board, hero);
    const auto finish = std::make_shared<eKillCharacterFinishFail>(
                            board, hero);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(fail);
    a->setFinishAction(finish);
    a->setFindFailAction([cptr]() {
        if(cptr) cptr->kill();
    });
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);

    const auto exitPoint = board.exitPoint();
    if(exitPoint) {
        a->start(exitPoint);
    } else {
        const int bw = board.width();
        const int bh = board.height();
        const auto edgeTile = [bw, bh](eTileBase* const tile) {
            const int tx = tile->dx();
            if(tx == 0 || tx >= bw) return true;
            const int ty = tile->dy();
            if(ty == 0 || ty >= bh) return true;
            return false;
        };
        a->start(edgeTile);
    }
}

void eSoldierAction::beingAttacked(eCharacter* const ss) {
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
     } else if(t == eCharacterType::horseman) {
        v = [](eBuilding* const b) {
            const auto bt = b->type();
            if(bt != eBuildingType::eliteHousing) return false;
            const auto eh = static_cast<eEliteHousing*>(b);
            if(eh->level() < 4) return false;
            return true;
        };
    } else if(t == eCharacterType::amazon) {
        v = [](eBuilding* const b) {
            const auto bt = b->type();
            if(bt != eBuildingType::temple) return false;
            const auto eh = static_cast<eTempleBuilding*>(b);
            if(!eh->finished()) return false;
            const auto s = eh->sanctuary();
            if(s->godType() != eGodType::artemis) return false;
            return true;
        };
    } else if(t == eCharacterType::aresWarrior) {
        v = [](eBuilding* const b) {
            const auto bt = b->type();
            if(bt != eBuildingType::temple) return false;
            const auto eh = static_cast<eTempleBuilding*>(b);
            if(!eh->finished()) return false;
            const auto s = eh->sanctuary();
            if(s->godType() != eGodType::ares) return false;
            return true;
        };
    } else {
        return nullptr;
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

void eSoldierAction::goBackToBanner(const eAction& findFailAct,
                                    const eAction& findFinishAct) {
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
    goTo(ttx, tty, 0, findFailAct, findFinishAct);
}
