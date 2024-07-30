#include "eheroaction.h"

#include "characters/monsters/emonster.h"
#include "characters/heroes/ehero.h"

#include "characters/actions/egodmonsteraction.h"
#include "characters/actions/emovetoaction.h"
#include "characters/actions/epatrolmoveaction.h"
#include "characters/actions/edefendcityaction.h"
#include "ekillcharacterfinishfail.h"
#include "ewaitaction.h"
#include "engine/egameboard.h"
#include "vec2.h"
#include "buildings/eheroshall.h"

eHeroAction::eHeroAction(eCharacter* const c) :
    eActionWithComeback(c, eCharActionType::heroAction) {
    setFinishOnComeback(true);
}

bool eHeroAction::decide() {
    const auto c = character();
    if(mStage == eHeroActionStage::none) {
        mStage = eHeroActionStage::patrol;
        const auto failFunc = std::make_shared<eHA_patrolFail>(
                                  board(), this);
        const auto pa = e::make_shared<ePatrolMoveAction>(c);
        pa->setFailAction(failFunc);
        pa->setFinishAction(failFunc);
        pa->setMaxWalkDistance(200);
        setCurrentAction(pa);
        c->setActionType(eCharacterActionType::walk);
    } else if(mStage == eHeroActionStage::goBack) {
        return false;
    } else {
        mStage = eHeroActionStage::goBack;
        if(mQuestWaiting) {
            mQuestWaiting = false;
            sendOnQuest();
        } else {
            c->setActionType(eCharacterActionType::walk);
            goBack(defaultWalkable());
        }
    }
    return true;
}

void eHeroAction::increment(const int by) {
    if(mStage == eHeroActionStage::patrol ||
       mStage == eHeroActionStage::goBack) {
        const int lookForMonsterCheck = 10000;
        mLookForMonster += by;
        if(mLookForMonster > lookForMonsterCheck) {
            mLookForMonster -= lookForMonsterCheck;
            lookForMonster();
        }
        const int lookForCityDefenseCheck = 5000;
        mLookForCityDefense += by;
        if(mLookForCityDefense > lookForCityDefenseCheck) {
            mLookForCityDefense -= lookForCityDefenseCheck;
            defendCity();
        }
    }
    if(mStage == eHeroActionStage::hunt) {
        lookForMonsterFight();
    }
    eActionWithComeback::increment(by);
}

void eHeroAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    src >> mStage;
    src >> mLookForMonster;
    src >> mLookForCityDefense;
    src >> mQuestWaiting;
}

void eHeroAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst << mStage;
    dst << mLookForMonster;
    dst << mLookForCityDefense;
    dst << mQuestWaiting;
}

void eHeroAction::lookForMonster() {
    const auto c = character();
    const auto ct = c->type();
    const auto ht = eHero::sCharacterToHeroType(ct);
    const auto& board = eHeroAction::board();
    const auto& ms = board.monsters();
    for(const auto m : ms) {
        if(m->dead()) continue;
        const auto ct = m->type();
        const auto mt = eMonster::sCharacterToMonsterType(ct);
        const auto sl = eMonster::sSlayer(mt);
        if(sl != ht) continue;
        huntMonster(m, false);
    }
}

void eHeroAction::sendOnQuest() {
    if(mStage == eHeroActionStage::fight) {
        mQuestWaiting = true;
        return;
    }
    const auto c = character();
    auto& board = eHeroAction::board();
    const auto hero = static_cast<eHero*>(c);
    const stdptr<eHero> cptr(hero);
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
        a->start(exitPoint, defaultWalkable());
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
        a->start(edgeTile, defaultWalkable());
    }
}

void eHeroAction::goBackToHall() {
    auto& board = eHeroAction::board();
    const auto hh = board.heroHall(heroType());
    if(!hh) return;
    const auto c = character();
    const auto hero = static_cast<eHero*>(c);
    const stdptr<eHero> cptr(hero);
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
    a->start(hh, defaultWalkable());
}

void eHeroAction::waitAndGoBackToHall(const int w) {
    const auto c = character();
    c->setActionType(eCharacterActionType::none);
    const auto finish = std::make_shared<eHA_waitAndGoToHallFinish>(
                            board(), this);
    const auto a = e::make_shared<eWaitAction>(c);
    a->setFinishAction(finish);
    a->setTime(w);
    setCurrentAction(a);
}

void eHeroAction::defendCity() {
    auto& board = eHeroAction::board();
    const auto i = board.invasionToDefend();
    if(!i) return;
    mStage = eHeroActionStage::defend;
    const auto c = character();
    const auto da = e::make_shared<eDefendCityAction>(c);
    setCurrentAction(da);
}

void eHeroAction::lookForMonsterFight() {
    const auto c = character();
    const auto ct = c->tile();
    if(!ct) return;
    const int tx = ct->x();
    const int ty = ct->y();
    auto& brd = c->getBoard();
    const auto ctype = c->type();
    const auto ht = eHero::sCharacterToHeroType(ctype);
    const bool ranged = rangedHero();
    const int range = ranged ? 5 : 1;
    for(int i = -range; i <= range; i++) {
        for(int j = -range; j <= range; j++) {
            const auto t = brd.tile(tx + i, ty + j);
            if(!t) continue;
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(cc->dead()) continue;
                const auto cctype = cc->type();
                bool monster;
                const auto mt = eMonster::sCharacterToMonsterType(cctype, &monster);
                if(!monster) continue;
                if(cc->playerId() == 1) continue;
                const auto sl = eMonster::sSlayer(mt);
                if(sl != ht) continue;
                const auto m = static_cast<eMonster*>(cc.get());
                const bool r = fightMonster(m);
                if(r) return;
            }
        }
    }
}

bool eHeroAction::fightMonster(eMonster* const m) {
    const bool ranged = rangedHero();

    const auto c = character();
    const vec2d cpos{c->absX(), c->absY()};
    const vec2d mpos{m->absX(), m->absY()};
    const vec2d posdif = mpos - cpos;
    const double dist = posdif.length();
    const double range = ranged ? 5. : 1.;
    if(dist > range) return false;
    const auto angle = posdif.angle();
    const auto o = sAngleOrientation(angle);
    c->setOrientation(o);
    c->setActionType(eCharacterActionType::fight);
    stdsptr<eCharacterAction> ca;
    const int fightTime = 5000;
    if(ranged) {
        const int attackTime = eHero::sHeroAttackTime(heroType());
        const auto gm = e::make_shared<eGodMonsterActionInd>(c);
        gm->spawnTimedMissiles(eCharacterActionType::fight,
                               c->type(), attackTime, m,
                               nullptr, nullptr, nullptr,
                               fightTime);
        ca = gm;
    } else {
        const auto w = e::make_shared<eWaitAction>(c);
        w->setTime(fightTime);
        ca = w;
    }
    const auto mdie = std::make_shared<eHA_fightMonsterDie>(
                          board(), m);
    ca->setFailAction(mdie);
    ca->setFinishAction(mdie);
    setCurrentAction(ca);

    if(!ranged) {
        const auto mo = !o;
        m->setOrientation(mo);
        m->setActionType(eCharacterActionType::fight);

        const auto mw = e::make_shared<eWaitAction>(c);
        m->setAction(mw);
    }

    mStage = eHeroActionStage::fight;

    return true;
}

void eHeroAction::huntMonster(eMonster* const m, const bool second) {
    const auto mt = m->tile();
    if(!mt) return;
    const int mtx = mt->x();
    const int mty = mt->y();
    const auto mtype = m->type();

    const auto c = character();

    const auto monsterTile = [mtx, mty](eTileBase* const tile) {
        return tile->x() == mtx && tile->y() == mty;
    };

    const auto finish = std::make_shared<eHA_huntMonsterFinish>(
                            board(), this);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(finish);
    a->setFinishAction(finish);
    const stdptr<eHeroAction> tptr(this);
    const stdptr<eMonster> mptr(m);
    a->setFoundAction([tptr, mptr, this, a, c, second]() {
        if(!tptr || !mptr) return;
        if(second) {
            mStage = eHeroActionStage::hunt;
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
        a->start(monsterTile, defaultWalkable());
    }
    if(second) {
        setCurrentAction(a);
    }
}

stdsptr<eWalkableObject> eHeroAction::defaultWalkable() const {
    const auto c = character();
    const auto tile = c->tile();
    const bool w = tile->hasWater();
    if(w) {
        return eWalkableObject::sCreateWaterAndDefault();
    } else {
        return eWalkableObject::sCreateDefault();
    }
}

eHeroType eHeroAction::heroType() const {
    const auto c = character();
    const auto ctype = c->type();
    const auto ht = eHero::sCharacterToHeroType(ctype);
    return ht;
}

bool eHeroAction::rangedHero() const {
    const auto ht = heroType();
    const bool r = eHero::sRangedHero(ht);
    return r;
}
