#include "eheroaction.h"

#include "characters/monsters/emonster.h"
#include "characters/heroes/ehero.h"

#include "characters/actions/emovetoaction.h"
#include "characters/actions/epatrolmoveaction.h"
#include "ewaitaction.h"
#include "engine/egameboard.h"
#include "vec2.h"

bool eHeroAction::decide() {
    setFinishOnComeback(true);

    const auto c = character();
    if(mStage == eHeroActionStage::none) {
        mStage = eHeroActionStage::patrol;
        const stdptr<eHeroAction> tptr(this);
        const auto failFunc = [tptr, this, c]() {
            if(!tptr) return;
            c->setActionType(eCharacterActionType::walk);
            goBack(eWalkableHelpers::sDefaultWalkable);
        };
        const auto pa = e::make_shared<ePatrolMoveAction>(
                            c, failFunc, failFunc);
        pa->setMaxWalkDistance(200);
        setCurrentAction(pa);
        c->setActionType(eCharacterActionType::walk);
    } else if(mStage == eHeroActionStage::goBack) {
        return false;
    } else {
        mStage = eHeroActionStage::goBack;
        c->setActionType(eCharacterActionType::walk);
        goBack(eWalkableHelpers::sDefaultWalkable);
    }
    return true;
}

void eHeroAction::increment(const int by) {
    if(mStage == eHeroActionStage::patrol) {
        const int lookForMonsterCheck = 10000;
        mLookForMonster += by;
        if(mLookForMonster > lookForMonsterCheck) {
            mLookForMonster -= lookForMonsterCheck;
            lookForMonster();
        }
    }
    if(mStage != eHeroActionStage::fight) {
        lookForMonsterFight();
    }
    eActionWithComeback::increment(by);
}

void eHeroAction::lookForMonster() {
    const auto c = character();
    const auto ct = c->type();
    const auto ht = eHero::sCharacterToHeroType(ct);
    const auto& board = c->getBoard();
    const auto& ms = board.monsters();
    for(const auto m : ms) {
        if(m->dead()) continue;
        const auto ct = m->type();
        const auto mt = eMonster::sCharacterToMonsterType(ct);
        const auto sl = eMonster::sSlayer(mt);
        if(sl != ht) continue;
        huntMonster(m);
        break;
    }
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
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            const auto t = brd.tile(tx + i, ty + j);
            if(!t) continue;
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(cc->dead()) continue;
                const auto cctype = cc->type();
                bool monster;
                const auto mt = eMonster::sCharacterToMonsterType(cctype, &monster);
                if(!monster) continue;
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
    const auto c = character();
    const vec2d cpos{c->absX(), c->absY()};
    const vec2d mpos{m->absX(), m->absY()};
    const vec2d posdif = mpos - cpos;
    const double dist = posdif.length();
    if(dist > 1.) return false;
    const auto angle = posdif.angle();
    const auto o = sAngleOrientation(angle);
    c->setOrientation(o);
    c->setActionType(eCharacterActionType::fight);
    const int fightTime = 5000;
    wait(fightTime);

    const auto mo = !o;
    m->setOrientation(mo);
    m->setActionType(eCharacterActionType::fight);
    const stdptr<eMonster> mptr(m);
    const auto mdie = [mptr, m]() {
        if(!mptr) return;
        m->killWithCorpse();
    };
    const auto w = e::make_shared<eWaitAction>(
                       character(), mdie, mdie);
    w->setTime(fightTime);
    m->setAction(w);

    mStage = eHeroActionStage::fight;

    return true;
}

void eHeroAction::huntMonster(eMonster* const m) {
    const auto mt = m->tile();
    if(!mt) return;
    const int mtx = mt->x();
    const int mty = mt->y();

    const auto c = character();

    const stdptr<eHeroAction> tptr(this);
    const auto failFunc = [tptr, this, c]() {
        if(!tptr) return;
        c->setActionType(eCharacterActionType::walk);
        goBack(eWalkableHelpers::sDefaultWalkable);
    };

    const auto monsterTile = [mtx, mty](eTileBase* const tile) {
        return tile->x() == mtx && tile->y() == mty;
    };

    const stdptr<eMonster> mptr(m);
    const auto finish = [tptr, this, mptr]() {
        if(!tptr) return;
        if(!mptr) return;
        huntMonster(mptr);
    };

    const auto a = e::make_shared<eMoveToAction>(
                       c, failFunc, finish);
    a->setFoundAction([tptr, this, a, c]() {
        if(!tptr) return;
        mStage = eHeroActionStage::hunt;
        c->setActionType(eCharacterActionType::walk);
        setCurrentAction(a);
    });
    a->setRemoveLastTurn(true);
    a->setWait(false);
    a->start(monsterTile);
}
