#include "esoldieraction.h"

#include "characters/esoldier.h"
#include "engine/egameboard.h"

#include <math.h>
#include "epathdatafindtask.h"
#include "ewalkablehelpers.h"

#include "missiles/erockmissile.h"

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

void eSoldierAction::increment(const int by) {
    const int rangeAttackCheck = 500;
    const int lookForEnemyCheck = 500;
    const int missileCheck = 200;

    const auto c = character();
    const auto s = static_cast<eSoldier*>(c);
    const int range = s->range();
    auto& brd = c->getBoard();
    const auto ct = c->tile();
    const int tx = ct->x();
    const int ty = ct->y();
    const int pid = c->playerId();

    if(mAttack) {
        if(range > 0 && mAttackTarget.valid()) {
            mMissile += by;
            if(mMissile > missileCheck) {
                mMissile = mMissile - missileCheck;
                const auto tt = mAttackTarget.tile();
                const int ttx = tt->x();
                const int tty = tt->y();
                eMissile::sCreate<eRockMissile>(brd, tx, ty, 0.5,
                                                ttx, tty, 0.5, 2);
            }
        }
        mAttackTime += by;
        bool finishAttack = !mAttackTarget.valid() ||
                            mAttackTarget.dead() ||
                            mAttackTime > 1000;
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
            c->setActionType(eCharacterActionType::walk);
        } else {
            return;
        }
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
            const auto ub = t->underBuilding();
            if(!ub) continue;
            if(ub->playerId() == pid) continue;
            mAttackTarget = eAttackTarget(ub);
            mAttack = true;
            mAttackTime = 0;
            c->setActionType(eCharacterActionType::fight);
            const vec2d ccpos{1.*t->x(), 1.*t->y()};
            const vec2d posdif = ccpos - cpos;
            mAngle = posdif.angle();
            const auto o = sAngleOrientation(mAngle);
            c->setOrientation(o);
        }
    }

    if(range > 0) {
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
                        mAttackTarget = eAttackTarget(cc.get());
                        mAttack = true;
                        mAttackTime = 0;
                        c->setActionType(eCharacterActionType::fight2);
                        mAngle = posdif.angle();
                        const auto o = sAngleOrientation(mAngle);
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
                                    aaa->beingAttacked(s);
                                }
                            }
                        }

                        return;
                    }
                }
            }
        }
    }

    if(!hasForce(eForceType::reserved1)) {
        mLookForEnemy += by;
        if(mLookForEnemy > lookForEnemyCheck) {
            mLookForEnemy = 0;
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
                        setPathForce(tx, ty, ttx, tty, range);
                        break;
                    }
                }
            }
        }
    }
    if(!mForceGetters.empty()) {
        vec2d force{0, 0};
        const auto frcs = mForceGetters;
        for(const auto& frc : frcs) {
            force += frc.second(c);
        }
        const double len = force.length();
        if(abs(len) > 0.001) {
            const double d = c->speed()*0.005 * by;
            force *= d/len;
            moveBy(force.x, force.y);
            const auto degAngle = force.angle();
            mAngle = mAngle*0.9 + 0.1*degAngle;
            const auto o = sAngleOrientation(mAngle);
            c->setOrientation(o);
        } else {
            c->setActionType(eCharacterActionType::walk);
        }
    } else {
    }
}

int eSoldierAction::addForce(const eForceGetter& force,
                             const eForceType type) {
    switch(type) {
    case eForceType::regular:
        mForceGetters[mForceId] = force;
        return mForceId++;
    case eForceType::reserved1:
        mForceGetters[-1] = force;
        return -1;
    }
}

void eSoldierAction::removeForce(const int id) {
    mForceGetters.erase(id);
}

void eSoldierAction::removeForce(const eForceType type) {
    switch(type) {
    case eForceType::regular:
        break;
    case eForceType::reserved1:
        mForceGetters.erase(-1);
        break;
    }
}

int forceTypeId(const eForceType type) {
    switch(type) {
    case eForceType::regular:
        return 0;
    case eForceType::reserved1:
        return -1;
    }
}

bool eSoldierAction::hasForce(const eForceType type) const {
    const int i = forceTypeId(type);
    const auto it = mForceGetters.find(i);
    const auto end = mForceGetters.end();
    return it != end;
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

void eSoldierAction::setPathForce(const int sx, const int sy,
                                  const int fx, const int fy,
                                  const int dist) {

    const auto startTile = [fx, fy](eThreadBoard& board) {
        return board.absTile(fx, fy);
    };

    const auto endTile = [sx, sy, dist](eTileBase* const t) {
        return abs(t->x() - sx) <= dist && abs(t->y() - sy) <= dist;
    };

    const stdptr<eSoldierAction> a = this;
    const auto finishFunc = [a](const ePathFindData& data) {
        if(!a) return;
        const auto c = a->character();
        c->setActionType(eCharacterActionType::walk);
        a->addForce([a, data](eCharacter* const c) {
            const auto& brd = data.fBoard;
            vec2d force{0., 0.};
            const auto t = c->tile();
            const int tx = t->x();
            const int ty = t->y();
            int v;
            const bool r = brd.getAbsValue(tx, ty, v);
            if(!r) return vec2d{0., 0.};
            if(v == 0 && a) {
                a->removeForce(eForceType::reserved1);
            }
            bool found = false;
            for(int i = -1; i <= 1 && !found; i++) {
                for(int j = -1; j <= 1 && !found; j++) {
                    if(i == 0 && j == 0) continue;
                    const int ttx = tx + i;
                    const int tty = ty + j;
                    int vv;
                    const bool r = brd.getAbsValue(ttx, tty, vv);
                    if(!r) continue;
                    if(vv >= v) continue;
                    found = true;
                    force = vec2d{1.*i, 1.*j};
                    break;
                }
            }
            force.normalize();
            return force;
        }, eForceType::reserved1);
    };

    const auto c = character();
    auto& brd = c->getBoard();
    auto& tp = brd.threadPool();

    const auto pft = new ePathDataFindTask(
                         startTile, eWalkableHelpers::sDefaultWalkable,
                         endTile, finishFunc, [](){}, false, 1000);
    tp.queueTask(pft);
}

void eSoldierAction::beingAttacked(eSoldier* const ss) {
    const auto tt = ss->tile();
    const int ttx = tt->x();
    const int tty = tt->y();
    beingAttacked(ttx, tty);
}

void eSoldierAction::beingAttacked(const int ttx, const int tty) {
    if(mAttack) return;
    if(hasForce(eForceType::reserved1)) return;
    const auto c = character();
    const auto t = c->tile();
    const int tx = t->x();
    const int ty = t->y();
    setPathForce(tx, ty, ttx, tty);
}
