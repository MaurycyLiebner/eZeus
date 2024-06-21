#include "edefendcityaction.h"

#include "characters/echaracter.h"
#include "engine/egameboard.h"
#include "gameEvents/einvasionevent.h"
#include "egodaction.h"
#include "emovetoaction.h"
#include "vec2.h"
#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"

eDefendCityAction::eDefendCityAction(eCharacter* const c) :
    eGodMonsterAction(c, eCharActionType::defendCityAction) {}

bool eDefendCityAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eDefendCityStage::none:
        mStage = eDefendCityStage::appear;
        if(!c->tile()) randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eDefendCityStage::appear:
        mStage = eDefendCityStage::goTo;
        mStartTile = c->tile();
        goToTarget();
        break;
    case eDefendCityStage::goTo:
    case eDefendCityStage::wait: {
        if(!mEvent) {
            mStage = eDefendCityStage::comeback;
            goBack();
        } else {
            auto& board = eDefendCityAction::board();
            const auto date = board.date();
            const auto eDate = mEvent->startDate();
            if(date > eDate) {
                mStage = eDefendCityStage::fight;
                moveAround();
            } else {
                mStage = eDefendCityStage::wait;
                moveAround();
            }
        }
    }   break;
    case eDefendCityStage::fight:
        mStage = eDefendCityStage::comeback;
        goBack();
        break;
    case eDefendCityStage::comeback:
        mStage = eDefendCityStage::disappear;
        disappear();
        break;
    case eDefendCityStage::disappear:
        c->kill();
        break;
    }
    return true;
}

void eDefendCityAction::increment(const int by) {
    const int rangeAttackCheck = 500;
    const int lookForEnemyCheck = 500;
    int missileCheck = 200;

    auto& brd = board();
    const auto c = character();
    if(c->dead()) return;
    const auto cTile = c->tile();
    if(!cTile) return;
    const int tx = cTile->x();
    const int ty = cTile->y();
    const int range = this->range();
    const int pid = c->playerId();
    const auto ct = c->type();

    if(mAttack) {
        if(range > 0 && mAttackTarget && mAttackTarget->tile()) {
            bool isGod;
            const auto gt = eGod::sCharacterToGodType(ct, &isGod);
            if(isGod) {
                missileCheck = eGod::sGodAttackTime(gt);
            } else {
                bool isHero;
                const auto ht = eHero::sCharacterToHeroType(ct, &isHero);
                if(isHero) {
                    missileCheck = eHero::sHeroAttackTime(ht);
                } else {
                    bool isMonster;
                    const auto mt = eMonster::sCharacterToMonsterType(ct, &isMonster);
                    if(isMonster) {
                        missileCheck = eMonster::sMonsterAttackTime(mt);
                    } else {
                        missileCheck = 200;
                    }
                }
            }
            mMissile += by;
            if(mMissile > missileCheck) {
                mMissile -= missileCheck;
                const auto tt = mAttackTarget->tile();
                spawnMissile(eCharacterActionType::fight,
                             ct, missileCheck, tt,
                             nullptr, nullptr);
            }
        }
        mAttackTime += by;
        bool finishAttack = !mAttackTarget ||
                            mAttackTarget->dead() ||
                            mAttackTime > 1000;
        if(mAttackTarget && !mAttackTarget->dead()) {
            const double att = by*c->attack();
            const bool d = mAttackTarget->defend(att);
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
                mAttackTarget = cc;
                mAttack = true;
                mAttackTime = 0;
                c->setActionType(eCharacterActionType::fight);
                mAngle = posdif.angle();
                const auto o = sAngleOrientation(mAngle);
                c->setOrientation(o);
                return;
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
                        mAttackTarget = cc;
                        mAttack = true;
                        mAttackTime = 0;
                        c->setActionType(eCharacterActionType::fight);
                        mAngle = posdif.angle();
                        const auto o = sAngleOrientation(mAngle);
                        c->setOrientation(o);
                        const auto ss = static_cast<eSoldier*>(cc.get());
                        eSoldierAction::sSignalBeingAttack(ss, c, brd);
                        return;
                    }
                }
            }
        }
    }

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

    eGodMonsterAction::increment(by);
}

void eDefendCityAction::read(eReadStream& src) {
    auto& board = eDefendCityAction::board();
    eGodMonsterAction::read(src);
    src.readGameEvent(&board, [this](eGameEvent* const e) {
        mEvent = static_cast<eInvasionEvent*>(e);
    });
    src >> mStage;
    mStartTile = src.readTile(board);
    src.readCharacter(&board, [this](eCharacter* const c) {
        mAttackTarget = c;
    });
    src >> mAttack;
    src >> mLookForEnemy;
    src >> mAttackTime;
    src >> mRangeAttack;
    src >> mAngle;
    src >> mMissile;
}

void eDefendCityAction::write(eWriteStream& dst) const {
    eGodMonsterAction::write(dst);
    dst.writeGameEvent(mEvent);
    dst << mStage;
    dst.writeTile(mStartTile);
    dst.writeCharacter(mAttackTarget);
    dst << mAttack;
    dst << mLookForEnemy;
    dst << mAttackTime;
    dst << mRangeAttack;
    dst << mAngle;
    dst << mMissile;
}

void eDefendCityAction::goToTarget() {
    auto& board = eDefendCityAction::board();
    mEvent = board.invasionToDefend();
    if(!mEvent) {
        mStage = eDefendCityStage::comeback;
        return;
    }
    const int ip = mEvent->invasionPoint();
    const auto tile = board.landInvasionTile(ip);
    if(!tile) {
        mStage = eDefendCityStage::comeback;
        return;
    }
    using eGTTT = eGoToTargetTeleport;
    const auto tele = std::make_shared<eGTTT>(board, this);
    goToTile(tile, tele);
}

void eDefendCityAction::goBack() {
    auto& board = eDefendCityAction::board();
    using eGTTT = eGoToTargetTeleport;
    const auto tele = std::make_shared<eGTTT>(board, this);
    goToTile(mStartTile, tele);
}

void eDefendCityAction::goTo(const int fx, const int fy, const int dist) {
    const auto c = character();
    const auto t = c->tile();
    const int sx = t->x();
    const int sy = t->y();
    if(abs(fx - sx) <= dist && abs(fy - sy) <= dist) return;

    const auto hha = [fx, fy, dist](eThreadTile* const t) {
        return abs(t->x() - fx) <= dist && abs(t->y() - fy) <= dist;
    };

    const auto walkable =
        eWalkableObject::sCreateDefault();

    const auto a = e::make_shared<eMoveToAction>(c);

    const stdptr<eCharacter> cptr(character());
    const stdptr<eDefendCityAction> tptr(this);
    a->setFoundAction([cptr, tptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });
    a->start(hha, walkable, nullptr,
             [fx, fy](eThreadBoard& board) {
        return board.tile(fx, fy);
    });
    setCurrentAction(a);
}

int eDefendCityAction::range() const {
    const auto c = character();
    const auto ct = c->type();
    switch(ct) {
    case eCharacterType::atalanta:
        return 5;
    case eCharacterType::artemis:
    case eCharacterType::apollo:
        return 5;
    default:
        return 0;
    }
    return 0;
}
