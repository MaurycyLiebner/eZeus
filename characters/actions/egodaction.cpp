#include "egodaction.h"

#include "engine/egameboard.h"
#include "audio/esounds.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "epatrolmoveaction.h"

#include "eiteratesquare.h"

#include "missiles/egodmissile.h"

#include "emovetoaction.h"

eGodAction::eGodAction(eCharacter* const c, const eCharActionType type) :
    eGodMonsterAction(c, type),
    mType(eGod::sCharacterToGodType(c->type())) {}

void eGodAction::appear() {
    if(type() == eGodType::hermes) {
        hermesRun(true);
    } else {
        const auto c = character();
        c->setActionType(eCharacterActionType::appear);
        const auto a = e::make_shared<eWaitAction>(c);
        a->setTime(500);
        setCurrentAction(a);
        playAppearSound();
    }
}

void eGodAction::disappear(const bool die,
                           const stdsptr<eCharActFunc>& finish) {
    if(type() == eGodType::hermes) {
        hermesRun(false);
    } else {
        const auto c = character();
        c->setActionType(die ? eCharacterActionType::die :
                               eCharacterActionType::disappear);
        const auto a = e::make_shared<eWaitAction>(c);
        a->setFinishAction(finish);
        a->setFailAction(finish);
        a->setTime(500);
        setCurrentAction(a);
        playDisappearSound();
    }
}

void eGodAction::teleport(eTile* const tile) {
    const stdptr<eGodAction> tptr(this);
    const auto finish = std::make_shared<eGA_teleportFinish>(
                            board(), this, tile);
    disappear(false, finish);
}

void eGodAction::patrol(const stdsptr<eCharActFunc>& finishAct,
                        const int dist) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const stdptr<eGodAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto failAct = std::make_shared<eGA_patrolFail>(
                             board(), this, c, finishAct, dist);
    const auto a = e::make_shared<ePatrolMoveAction>(c);
    a->setFailAction(failAct);
    a->setFinishAction(finishAct);
    a->setMaxWalkDistance(dist);
    setCurrentAction(a);
}

void eGodAction::playAppearSound() {
    const auto c = character();
    auto& board = c->getBoard();
    board.ifVisible(c->tile(), [this]() {
        eSounds::playGodSound(type(), eGodSound::appear);
    });
}

void eGodAction::playDisappearSound() {
    const auto c = character();
    auto& board = c->getBoard();
    board.ifVisible(c->tile(), [this]() {
        eSounds::playGodSound(type(), eGodSound::disappear);
    });
}

void eGodAction::hermesRun(const bool appear) {
    const auto c = character();
    c->setActionType(eCharacterActionType::appear);
    c->setSpeed(2.0);
    const auto tile = c->tile();
    const stdptr<eGodAction> tptr(this);
    const auto finish = std::make_shared<eGA_hermesRunFinish>(
                            board(), this, c, appear);
    if(tile->hasRoad()) {
        patrol(finish, 20);
    } else {
        moveAround(finish, 1000);
    }
    if(appear) playAppearSound();
}

void eGodAction::randomPlaceOnBoard() {
    const auto c = character();
    auto& board = c->getBoard();
    const int w = board.width();
    const int h = board.height();
    const int rdx = rand() % w;
    const int rdy = rand() % h;
    int tx;
    int ty;
    eTileHelper::dtileIdToTileId(rdx, rdy, tx, ty);
    const auto tile = eTileHelper::closestRoad(tx, ty, board);
    if(!tile) return;
    c->changeTile(tile);
}

bool eGodAction::lookForBlessCurse(const int dtime,
                                   int& time, const int freq,
                                   const int range,
                                   const double bless) {
    const auto act = std::make_shared<eLookForBlessGodAct>(
                         board(), bless);
    eCharacterActionType at;
    eGodSound s;
    if(bless > 0) {
        at = eCharacterActionType::bless;
        s = eGodSound::santcify;
    } else {
        at = eCharacterActionType::curse;
        s = eGodSound::curse;
    }
    const auto c = character();
    const auto chart = c->type();
    return lookForRangeAction(dtime, time, freq, range,
                              at, act, chart, s);
}

bool eGodAction::lookForSoldierAttack(const int dtime, int& time,
                                      const int freq, const int range) {
    const auto act = std::make_shared<eLookForSoldierAttackGodAct>(
                         board());

    const auto at = eCharacterActionType::fight;
    const auto s = eGodSound::attack;

    const auto c = character();
    const auto chart = c->type();
    return lookForRangeAction(dtime, time, freq, range,
                              at, act, chart, s);
}

bool eGodAction::lookForRangeAction(const int dtime,
                                    int& time, const int freq,
                                    const int range,
                                    const eCharacterActionType at,
                                    const stdsptr<eGodAct>& act,
                                    const eCharacterType chart,
                                    const eGodSound missileSound) {
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
        std::vector<eTile*> tiles;
        const int rr = 2*range + 1;
        tiles.reserve(rr*rr);
        for(int i = -range; i <= range; i++) {
            for(int j = -range; j <= range; j++) {
                const int ttx = tx + i;
                const int tty = ty + j;
                const auto t = brd.tile(ttx, tty);
                if(!t) continue;
                tiles.push_back(t);
            }
        }
        std::random_shuffle(tiles.begin(), tiles.end());
        for(const auto t : tiles) {
            const auto tt = act->find(t);
            if(!tt) continue;

            const auto finishAttackA =
                    std::make_shared<eGA_lookForRangeActionFinish>(
                        board(), this);

            pauseAction();
            spawnGodMissile(at, chart, tt,
                            missileSound, act,
                            finishAttackA);
            return true;
        }
    }
    return false;
}

void eGodAction::spawnGodMissile(const eCharacterActionType at,
                                 const eCharacterType chart,
                                 eTile* const target,
                                 const eGodSound sound,
                                 const stdsptr<eGodAct>& act,
                                 const stdsptr<eCharActFunc>& finishAttackA) {
    const int time = eGod::sGodAttackTime(type());
    const auto c = character();
    const auto playSound = std::make_shared<eGA_spawnGodMissilePlaySound>(
                               board(), sound, c);
    spawnMissile(at, chart, time, target,
                 playSound, act, finishAttackA);
}

void eGodAction::spawnGodMultipleMissiles(const eCharacterActionType at,
                                          const eCharacterType chart,
                                          eTile* const target,
                                          const eGodSound sound,
                                          const stdsptr<eGodAct>& playHitSound,
                                          const stdsptr<eCharActFunc>& finishA,
                                          const int nMissiles) {
    const int time = eGod::sGodAttackTime(type());
    const auto c = character();
    const auto playSound = std::make_shared<eGA_spawnGodMissilePlaySound>(
                               board(), sound, c);
    spawnMultipleMissiles(at, chart, time, target,
                          playSound, playHitSound,
                          finishA, nMissiles);
}

void eGodAction::spawnGodTimedMissiles(const eCharacterActionType at,
                                       const eCharacterType chart,
                                       eTile* const target,
                                       const eGodSound sound,
                                       const stdsptr<eGodAct>& playHitSound,
                                       const stdsptr<eCharActFunc>& finishA,
                                       const int time) {
    const int atime = eGod::sGodAttackTime(type());
    const int n = std::round(double(time)/atime);
    spawnGodMultipleMissiles(at, chart, target, sound, playHitSound, finishA, n);
}

void eGodAction::fightGod(eGod* const g, const stdsptr<eCharActFunc>& finishAttackA) {
    const auto at = eCharacterActionType::fight;
    const auto s = eGodSound::attack;
    const auto playHitSound = std::make_shared<ePlayFightGodHitSoundGodAct>(
                                  board(), g);
    const auto c = character();
    spawnGodTimedMissiles(at, c->type(), g->tile(), s,
                          playHitSound, finishAttackA, 6000);
}

void eGodAction::goToTarget() {
    const auto gt = type();
    const auto hg = eHeatGetters::godLeaning(gt);
    const stdptr<eGodAction> tptr(this);
    const auto tele = std::make_shared<eGoToTargetTeleport>(
                          board(), this);
    eGodMonsterAction::goToTarget(hg, tele);
}
