#include "egodworshippedaction.h"

#include "characters/actions/edefendcityaction.h"
#include "characters/actions/emovetoaction.h"
#include "characters/actions/eheroaction.h"
#include "vec2.h"
#include "enumbers.h"

eGodWorshippedAction::eGodWorshippedAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::godWorshippedAction) {}

void eGodWorshippedAction::increment(const int by) {
    const int blessPeriod = eNumbers::sGodWorshippedBlessPeriod;
    const int blessRange = eNumbers::sGodWorshippedBlessRange;
    const bool r = lookForTargetedBlessCurse(by, mLookForBless,
                                             blessPeriod, blessRange, 1);
    if(!r) {
        const int attackPeriod = eNumbers::sGodWorshippedSoldierAttackPeriod;
        const int attackRange = eNumbers::sGodWorshippedSoldierAttackRange;
        const bool r = lookForSoldierAttack(by, mLookForSoldierAttack,
                                            attackPeriod, attackRange);
        if(!r) {
            if(mStage != eGodWorshippedStage::defend &&
               mStage != eGodWorshippedStage::huntMonster &&
               mStage != eGodWorshippedStage::fightMonster) {
                const auto t = type();
                if(t == eGodType::apollo) {
                    const int lookForMonsterCheck = 10000;
                    mLookForMonster += by;
                    if(mLookForMonster > lookForMonsterCheck) {
                        mLookForMonster -= lookForMonsterCheck;
                        lookForMonster();
                    }
                }
                const int lookForCityDefenseCheck = 5000;
                mLookForCityDefense += by;
                if(mLookForCityDefense > lookForCityDefenseCheck) {
                    mLookForCityDefense -= lookForCityDefenseCheck;
                    defendCity();
                }
            }
        }
    }
    if(mStage == eGodWorshippedStage::huntMonster) {
        lookForMonsterFight();
    }

    eGodAction::increment(by);
}

bool eGodWorshippedAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodWorshippedStage::none:
        mStage = eGodWorshippedStage::appear;
        if(!c->tile()) randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodWorshippedStage::defend:
    case eGodWorshippedStage::huntMonster:
    case eGodWorshippedStage::fightMonster:
    case eGodWorshippedStage::appear:
        mStage = eGodWorshippedStage::goTo1;
        goToTarget();
        break;
    case eGodWorshippedStage::goTo1: {
        mStage = eGodWorshippedStage::patrol1;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodWorshippedStage::patrol1:
        mStage = eGodWorshippedStage::goTo2;
        goToTarget();
        break;
    case eGodWorshippedStage::goTo2: {
        mStage = eGodWorshippedStage::patrol2;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodWorshippedStage::patrol2:
        mStage = eGodWorshippedStage::disappear;
        disappear();
        break;
    case eGodWorshippedStage::disappear:
        c->kill();
        break;
    }
    return true;
}

void eGodWorshippedAction::lookForMonster() {
    const auto& board = eGodWorshippedAction::board();
    const auto& ms = board.monsters();
    for(const auto m : ms) {
        if(m->dead()) continue;
        huntMonster(m, false);
    }
}

void eGodWorshippedAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src >> mLookForBless;
    src >> mLookForSoldierAttack;
    src >> mLookForCityDefense;
    src >> mLookForMonster;
}

void eGodWorshippedAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst << mLookForBless;
    dst << mLookForSoldierAttack;
    dst << mLookForCityDefense;
    dst << mLookForMonster;
}

void eGodWorshippedAction::defendCity() {
    auto& board = eGodWorshippedAction::board();
    const auto i = board.invasionToDefend();
    if(!i) return;
    mStage = eGodWorshippedStage::defend;
    const auto c = character();
    const auto da = e::make_shared<eDefendCityAction>(c);
    setCurrentAction(da);
}

void eGodWorshippedAction::lookForMonsterFight() {
    const auto c = character();
    const auto ct = c->tile();
    if(!ct) return;
    const int tx = ct->x();
    const int ty = ct->y();
    auto& brd = c->getBoard();
    const int range = 5;
    for(int i = -range; i <= range; i++) {
        for(int j = -range; j <= range; j++) {
            const auto t = brd.tile(tx + i, ty + j);
            if(!t) continue;
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(cc->dead()) continue;
                const auto cctype = cc->type();
                bool monster;
                eMonster::sCharacterToMonsterType(cctype, &monster);
                if(!monster) continue;
                if(cc->playerId() == 1) continue;
                const auto m = static_cast<eMonster*>(cc.get());
                const bool r = fightMonster(m);
                if(r) return;
            }
        }
    }
}

bool eGodWorshippedAction::fightMonster(eMonster* const m) {
    const auto c = character();
    const vec2d cpos{c->absX(), c->absY()};
    const vec2d mpos{m->absX(), m->absY()};
    const vec2d posdif = mpos - cpos;
    const double dist = posdif.length();
    const double range = 5.;
    if(dist > range) return false;
    const auto angle = posdif.angle();
    const auto o = sAngleOrientation(angle);
    c->setOrientation(o);
    c->setActionType(eCharacterActionType::fight);
    stdsptr<eCharacterAction> ca;
    const int fightTime = 5000;
    const int attackTime = eGod::sGodAttackTime(type());
    const auto gm = e::make_shared<eGodMonsterActionInd>(c);
    gm->spawnTimedMissiles(eCharacterActionType::fight,
                           c->type(), attackTime, m,
                           nullptr, nullptr, nullptr,
                           fightTime);
    ca = gm;
    const auto mdie = std::make_shared<eHA_fightMonsterDie>(
                          board(), m);
    ca->setFailAction(mdie);
    ca->setFinishAction(mdie);
    setCurrentAction(ca);

    mStage = eGodWorshippedStage::fightMonster;

    return true;
}

void eGodWorshippedAction::huntMonster(eMonster* const m, const bool second) {
    const auto mt = m->tile();
    if(!mt) return;
    const int mtx = mt->x();
    const int mty = mt->y();
    const auto mtype = m->type();

    const auto c = character();

    const auto monsterTile = [mtx, mty](eTileBase* const tile) {
        return tile->x() == mtx && tile->y() == mty;
    };

    const auto finish = std::make_shared<eGWA_huntMonsterFinish>(
                            board(), this);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(finish);
    a->setFinishAction(finish);
    const stdptr<eGodWorshippedAction> tptr(this);
    const stdptr<eMonster> mptr(m);
    a->setFoundAction([tptr, mptr, this, a, c, second]() {
        if(!tptr || !mptr) return;
        if(second) {
            mStage = eGodWorshippedStage::huntMonster;
            c->setActionType(eCharacterActionType::walk);
        } else {
            huntMonster(mptr, true);
        }
    });
    a->setRemoveLastTurn(true);
    a->setWait(false);
    if(mtype == eCharacterType::scylla ||
       mtype == eCharacterType::kraken) {
        a->start(monsterTile, eWalkableObject::sCreateWaterAndDefault());
    } else {
        a->start(monsterTile, eWalkableObject::sCreateDefault());
    }
    if(second) {
        setCurrentAction(a);
    }
}
