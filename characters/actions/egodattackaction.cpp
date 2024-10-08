#include "egodattackaction.h"

#include "buildings/ebuilding.h"
#include "engine/egameboard.h"
#include "edionysusfollowaction.h"
#include "characters/monsters/ecalydonianboar.h"
#include "characters/actions/ewaitaction.h"
#include "buildings/epalace.h"
#include "enumbers.h"

eGodAttackAction::eGodAttackAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::godAttackAction) {}

void eGodAttackAction::increment(const int by) {
    const auto c = character();
    const auto type = this->type();
    const auto at = c->actionType();
    if(at == eCharacterActionType::walk) {
        const int cursePeriod = eNumbers::sGodAttackCursePeriod;
        const int curseRange = eNumbers::sGodAttackCurseRange;
        const int lookForGodCheck = 1000;
        int attackPeriod;
        switch(type) {
        case eGodType::ares:
        case eGodType::artemis:
        case eGodType::athena:
        case eGodType::zeus:
            attackPeriod = eNumbers::sGodAttackAggressiveAttackPeriod;
            break;
        case eGodType::aphrodite:
        case eGodType::apollo:
        case eGodType::atlas:
        case eGodType::demeter:
        case eGodType::dionysus:
        case eGodType::hades:
        case eGodType::hephaestus:
        case eGodType::hera:
        case eGodType::hermes:
        case eGodType::poseidon:
        default:
            attackPeriod = eNumbers::sGodAttackAttackPeriod;
            break;
        }
        const int attackRange = eNumbers::sGodAttackAttackRange;

        const int targetedAttackPeriod = eNumbers::sGodAttackTargetedAttackPeriod;
        const int targetedAttackRange = eNumbers::sGodAttackTargetedAttackRange;
        const int targetedCursePeriod = eNumbers::sGodAttackTargetedCursePeriod;
        const int targetedCurseRange = eNumbers::sGodAttackTargetedCurseRange;
        const int godFightRange = eNumbers::sGodAttackGodFightRange;

        bool r = lookForBlessCurse(by, mLookForCurse, cursePeriod, curseRange, -1);
        if(!r) r = lookForAttack(by, mLookForAttack, attackPeriod, attackRange);
        if(!r) r = lookForTargetedAttack(by, mLookForTargetedAttack,
                                         targetedAttackPeriod, targetedAttackRange);
        if(!r) r = lookForTargetedBlessCurse(by, mLookForTargetedCurse,
                                             targetedCursePeriod, targetedCurseRange, -1);
        if(!r) lookForGodAttack(by, mLookForGod, lookForGodCheck, godFightRange);
        if(!r) {
            if(type == eGodType::apollo) {
                auto& board = this->board();
                using eLFPG = eLookForPlagueGodAct;
                const auto act = std::make_shared<eLFPG>(board);
                const auto at = eCharacterActionType::curse;
                const auto s = eGodSound::curse;
                const auto c = character();
                const auto chart = c->type();
                const int plaguePeriod = eNumbers::sGodAttackApolloPlaguePeriod;
                const int plagueRange = eNumbers::sGodAttackApolloPlagueRange;
                lookForRangeAction(by, mLookForSpecial,
                                   plaguePeriod, plagueRange,
                                   at, act, chart, s);
            } else if(type == eGodType::aphrodite) {
                auto& board = this->board();
                using eLFEG = eLookForEvictGodAct;
                const auto act = std::make_shared<eLFEG>(board);
                const auto at = eCharacterActionType::curse;
                const auto s = eGodSound::curse;
                const auto c = character();
                const auto chart = c->type();
                const int evictPeriod = eNumbers::sGodAttackAphroditeEvictPeriod;
                const int evictRange = eNumbers::sGodAttackAphroditeEvictRange;
                lookForRangeAction(by, mLookForSpecial,
                                   evictPeriod, evictRange,
                                   at, act, chart, s);
            }
        }
    }

    if(type == eGodType::atlas) {
        auto& board = this->board();
        const auto tile = c->tile();
        if(tile) {
            const auto& chars = tile->characters();
            for(const auto& cc : chars) {
                if(cc.get() == c) continue;
                const auto cType = cc->type();
                const bool r = eDionysusFollowAction::sShouldFollow(cType);
                if(!r) continue;
                const auto ccaa = cc->actionType();
                if(ccaa == eCharacterActionType::die) continue;
                const auto wa = e::make_shared<eWaitAction>(cc.get());
                wa->setTime(20000);
                cc->setActionType(eCharacterActionType::stand);
                cc->setAction(wa);
                const auto killA = std::make_shared<eChar_killWithCorpseFinish>(
                                       board, cc.get(), true);
                wa->setFinishAction(killA);
                wa->setFailAction(killA);
            }
        }
    }

    eGodAction::increment(by);
}

bool eGodAttackAction::lookForAttack(const int dtime,
                                     int& time, const int freq,
                                     const int range) {
    const auto c = character();
    const auto act = std::make_shared<eLookForAttackGodAct>(board(), c);

    const auto at = eCharacterActionType::fight2;
    const auto s = eGodSound::attack;
    const auto chart = c->type();

    return lookForRangeAction(dtime, time, freq, range,
                              at, act, chart, s);
}

bool eGodAttackAction::lookForTargetedAttack(const int dtime,
                                             int& time, const int freq,
                                             const int range) {
    const auto c = character();
    const auto act = std::make_shared<eLookForTargetedAttackGodAct>(
                         board(), type());

    const auto at = eCharacterActionType::fight2;
    const auto s = eGodSound::attack;
    const auto chart = c->type();

    return lookForRangeAction(dtime, time, freq, range,
                              at, act, chart, s);
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
                auto& board = thisGod->getBoard();
                const auto finishA = std::make_shared<eGAA_fightFinish>(
                                        board, winnerA, loserA, wt, lt);
                pauseAction();
                fightGod(otherGod, finishA);
                otherAction->pauseAction();
                otherAction->fightGod(thisGod, finishA);
            }
        }
    }
    return false;
}

stdsptr<eObsticleHandler> eGodAttackAction::obsticleHandler() {
    return std::make_shared<eGodObsticleHandler>(board(), this);
}

void eGodAttackAction::destroyBuilding(eBuilding* const b) {
    const auto finishAttackA = std::make_shared<eGAA_destroyBuildingFinish>(
                                   board(), this, b);
    const auto playHitSound = std::make_shared<ePlayMonsterBuildingAttackSoundGodAct>(
                                  board(), b);
    pauseAction();
    const auto at = eCharacterActionType::fight2;
    const auto s = eGodSound::attack;
    const auto c = character();
    const auto chart = c->type();
    spawnGodMultipleMissiles(at, chart, b->centerTile(),
                             s, playHitSound, finishAttackA, 3);
}

void eGodAttackAction::goToTarget() {
    const auto gt = type();
    const auto hg = eHeatGetters::godLeaning(gt);
    const stdptr<eGodAction> tptr(this);
    const auto tele = std::make_shared<eTeleportFindFailFunc>(board(), this);
    eGodMonsterAction::goToTarget(hg, tele, obsticleHandler());
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
        initialize();
        goToTarget();
        break;
    case eGodAttackStage::goTo1: {
        mStage = eGodAttackStage::patrol1;
        goToNearestRoad();
    }   break;
    case eGodAttackStage::patrol1:
        mStage = eGodAttackStage::goTo2;
        goToTarget();
        break;
    case eGodAttackStage::goTo2: {
        mStage = eGodAttackStage::patrol2;
        goToNearestRoad();
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

void eGodAttackAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src >> mLookForCurse;
    src >> mLookForTargetedCurse;
    src >> mLookForAttack;
    src >> mLookForTargetedAttack;
    src >> mLookForGod;
    src >> mLookForSpecial;
}

void eGodAttackAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst << mLookForCurse;
    dst << mLookForTargetedCurse;
    dst << mLookForAttack;
    dst << mLookForTargetedAttack;
    dst << mLookForGod;
    dst << mLookForSpecial;
}

void eGodAttackAction::initialize() {
    auto& board = this->board();
    const auto c = character();
    const auto tile = c->tile();
    if(!tile) return;
    const auto type = this->type();
    if(type == eGodType::dionysus) {
        eCharacter* f = c;
        eDionysusFollowAction* fa = nullptr;
        for(int i = 0; i < 3; i++) {
            const auto s = e::make_shared<eSatyr>(board);
            s->changeTile(tile);
            const auto a = e::make_shared<eDionysusFollowAction>(
                               f, s.get());
            s->setAction(a);
            f = s.get();
            if(fa) fa->setFollower(s.get());
            fa = a.get();
        }
    } else if(type == eGodType::hades) {
        const auto p = board.palace();
        if(p) p->setBlessed(-1.);
        const auto& chars = board.characters();
        for(const auto c : chars) {
            const auto cType = c->type();
            const bool r = eDionysusFollowAction::sShouldFollow(cType);
            if(!r) continue;
            if(c->dead()) continue;
            c->killWithCorpse();
        }
    }
}
