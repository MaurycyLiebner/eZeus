#include "earcheraction.h"

#include "epatrolmoveaction.h"

#include "characters/echaracter.h"
#include "buildings/ebuilding.h"
#include "engine/etile.h"
#include "engine/egameboard.h"
#include "vec2.h"
#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"
#include "characters/earcher.h"

#include "missiles/earrowmissile.h"

#include "edieaction.h"

void eArcherAction::increment(const int by) {
    const int rangeAttackCheck = 500;
    const int missileCheck = 200;
    const int range = 4;

    const auto c = character();
    const auto ct = c->tile();
    const int tx = ct->x();
    const int ty = ct->y();
    const vec2d cpos{c->absX(), c->absY()};
    const int pid = c->playerId();
    auto& brd = c->getBoard();

    if(mAttack) {
        if(range > 0 && mAttackTarget) {
            mMissile += by;
            if(mMissile > missileCheck) {
                mMissile = mMissile - missileCheck;
                const auto tt = mAttackTarget->tile();
                const int ttx = tt->x();
                const int tty = tt->y();
                eMissile::sCreate<eArrowMissile>(brd, tx, ty, 0.5,
                                                 ttx, tty, 0.5, 2);
            }
        }
        mAttackTime += by;
        bool finishAttack = !mAttackTarget ||
                            mAttackTarget->dead() ||
                            mAttackTime > 1000;
        if(mAttackTarget && !mAttackTarget->dead()) {
            const double att = by*c->attack();
            const bool d = mAttackTarget->defend(att);
            if(d) {
                const auto a = e::make_shared<eDieAction>(mAttackTarget, []() {});
                mAttackTarget->setAction(a);
                finishAttack = true;
            }
        }
        if(finishAttack) {
            mAttack = false;
            mAttackTarget = nullptr;
            mAttackTime = 0;
            mRangeAttack = rangeAttackCheck;
            c->setActionType(eCharacterActionType::walk);
        } else {
            return;
        }
    }

    mRangeAttack += by;
    if(mRangeAttack > rangeAttackCheck) {
        mRangeAttack = mRangeAttack - rangeAttackCheck;
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
                    mAttackTarget = cc;
                    mAttack = true;
                    mAttackTime = 0;
                    c->setActionType(eCharacterActionType::fight);
                    const double angle = posdif.angle();
                    const auto o = sAngleOrientation(angle);
                    c->setOrientation(o);

                    const auto tt = cc->tile();
                    const int ttx = tt->x();
                    const int tty = tt->y();
                    for(int ii = -2; ii <= 2; ii++) {
                        for(int jj = -2; jj <= 2; jj++) {
                            const auto tt = brd.tile(ttx + ii, tty + jj);
                            if(!tt) continue;
                            const auto& ccchars = tt->characters();
                            for(const auto& ccc : ccchars) {
                                if(!ccc->isSoldier()) continue;
                                if(ccc->playerId() == pid) continue;
                                if(ccc->dead()) continue;

                                const auto sss = static_cast<eSoldier*>(ccc.get());
                                const auto aaa = sss->soldierAction();
                                aaa->beingAttacked(tx, ty);
                            }
                        }
                    }

                    return;
                }
            }
        }
    }
    eComplexAction::increment(by);
}

bool eArcherAction::decide() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto walkable = [](eTileBase* const tile) {
        const auto ut = tile->underBuildingType();
        if(ut == eBuildingType::tower) return true;
        if(ut != eBuildingType::wall) return false;
        const auto bl = tile->tileRel(0, 1);
        if(!bl) return false;
        const auto br = tile->tileRel(1, 0);
        if(!br) return false;
        const auto b = tile->tileRel(1, 1);
        if(!b) return false;
        const auto blt = bl->underBuildingType();
        const auto brt = br->underBuildingType();
        const auto bt = b->underBuildingType();
        if(blt != eBuildingType::wall ||
           brt != eBuildingType::wall ||
           bt != eBuildingType::wall) return false;
        return true;
    };
    const auto fail = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finish = [this]() {
        setState(eCharacterActionState::finished);
    };
    const auto a = std::make_shared<ePatrolMoveAction>(
                       c, fail, finish, false, walkable);
    setCurrentAction(a);
    return true;
}
