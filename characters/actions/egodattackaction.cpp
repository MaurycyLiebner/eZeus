#include "egodattackaction.h"

#include "buildings/ebuilding.h"
#include "textures/edestructiontextures.h"
#include "esounds.h"
#include "engine/egameboard.h"
#include "elanguage.h"

void eGodAttackAction::increment(const int by) {
    const auto c = character();
    const auto at = c->actionType();
    if(at == eCharacterActionType::walk) {
        const int lookForCurseCheck = 6000;
        const int lookForAttackCheck = 8000;
        const int lookForGodCheck = 1000;

        bool r = lookForBlessCurse(by, mLookForCurse, lookForCurseCheck, 10, -1);
        if(!r) r = lookForAttack(by, mLookForAttack, lookForAttackCheck, 10);
        if(!r) lookForGodAttack(by, mLookForGod, lookForGodCheck, 10);
    }

    eGodAction::increment(by);
}

bool eGodAttackAction::lookForAttack(const int dtime,
                                     int& time, const int freq,
                                     const int range) {
    const auto c = character();
    const auto charTarget = std::make_shared<stdptr<eCharacter>>();
    const auto bTarget = std::make_shared<stdptr<eBuilding>>();
    const auto act = [c, charTarget, bTarget](eTile* const t) {
        const auto null = static_cast<eTile*>(nullptr);
        if(c->tile() == t) return null;
        const auto b = t->underBuilding();
        if(b && eBuilding::sAttackable(b->type())) {
            *bTarget = b;
            return b->centerTile();
        } else {
            const auto& chars = t->characters();
            if(chars.empty()) return null;
            for(const auto& cc : chars) {
                if(c == cc.get()) continue;
                bool isGod = false;
                eGod::sCharacterToGodType(cc->type(), &isGod);
                if(!isGod) {
                    *charTarget = cc;
                    return t;
                }
            }
            return null;
        }
    };

    const auto cptr = stdptr<eCharacter>(c);
    const auto finishA = [cptr, charTarget, bTarget]() {
        if(!cptr) return;
        if(*bTarget) {
            (*bTarget)->collapse();
            eSounds::playCollapseSound();
        } else if(*charTarget) {
            (*charTarget)->killWithCorpse();
        }
    };
    const auto at = eCharacterActionType::fight;
    const auto s = eGodSound::attack;
    const auto tex = eGod::sGodMissile(type());

    return lookForRangeAction(dtime, time, freq, range,
                              at, act, tex, s, finishA);
}

bool eGodAttackAction::lookForGodAttack(const int dtime, int& time,
                                        const int freq, const int range) {
    const auto c = character();
    const auto cat = c->actionType();
    const bool walking = cat == eCharacterActionType::walk;
    if(!walking) return false;
    auto& brd = c->getBoard();
    const auto ct = c->tile();
    if(!ct) return false;
    const int tx = ct->x();
    const int ty = ct->y();

    time += dtime;
    if(time > freq) {
        time -= freq;
        eGod* otherGod = nullptr;
        for(int i = -range; i <= range && !otherGod; i++) {
            for(int j = -range; j <= range; j++) {
                const int ttx = tx + i;
                const int tty = ty + j;
                const auto t = brd.tile(ttx, tty);
                if(!t) continue;
                const auto& chars = t->characters();
                for(const auto& ch : chars) {
                    if(const auto god = dynamic_cast<eGod*>(ch.get())) {
                        const auto att = god->attitude();
                        const auto at = god->actionType();
                        if(at != eCharacterActionType::walk) {
                            continue;
                        }
                        if(att == eGodAttitude::friendly ||
                           att == eGodAttitude::worshipped) {
                            otherGod = god;
                            break;
                        }
                    }
                }
            }
        }

        if(otherGod) {
            const auto aa = otherGod->action();
            if(const auto otherAction = dynamic_cast<eGodAction*>(aa)) {
                const auto thisGod = static_cast<eGod*>(c);
                const stdptr<eGod> g1ptr(thisGod);
                const stdptr<eGodAction> g1Aptr(this);
                const stdptr<eGod> g2ptr(otherGod);
                const stdptr<eGodAction> g2Aptr(otherAction);
                const auto g1t = g1ptr->type();
                const auto g2t = g2ptr->type();
                const auto wt = eGod::sFightWinner(g1t, g2t);
                const auto lt = g1t == wt ? g2t : g1t;
                const auto winnerA = g1t == wt ? g1Aptr : g2Aptr;
                const auto loserA = g1t == wt ? g2Aptr : g1Aptr;
                const auto board = &thisGod->getBoard();
                const auto finishA = [winnerA, loserA, wt, lt, board](){
                    if(winnerA) winnerA->resumeAction();
                    if(loserA) {
                        loserA->disappear(true, [loserA]() {
                            if(!loserA) return;
                            const auto c = loserA->character();
                            c->kill();
                        });
                    }
                    const auto wn = eGod::sGodName(wt);
                    const auto ln = eGod::sGodName(lt);
                    board->showTip(wn + eLanguage::text("overpowers") + ln);
                };
                pauseAction();
                fightGod(otherGod, finishA);
                otherAction->pauseAction();
                otherAction->fightGod(thisGod, finishA);
            }
        }
    }
    return false;
}

bool eGodAttackAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodAttackStage::none:
        mStage = eGodAttackStage::appear;
        randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodAttackStage::appear:
        mStage = eGodAttackStage::goTo1;
        goToTarget();
        break;
    case eGodAttackStage::goTo1: {
        mStage = eGodAttackStage::patrol1;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodAttackStage::patrol1:
        mStage = eGodAttackStage::goTo2;
        goToTarget();
        break;
    case eGodAttackStage::goTo2: {
        mStage = eGodAttackStage::patrol2;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodAttackStage::patrol2:
        mStage = eGodAttackStage::disappear;
        disappear();
        break;
    case eGodAttackStage::disappear:
        c->kill();
        break;
    }
    return true;
}
