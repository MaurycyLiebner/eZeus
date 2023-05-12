#include "egodmonsteraction.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "emovetoaction.h"
#include "engine/egameboard.h"
#include "engine/boardData/eheatmap.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "engine/boardData/eheatmaptask.h"

#include "etilehelper.h"

#include "egodattackaction.h"
#include "emonsteraction.h"
#include "epatrolmoveaction.h"

void eGodMonsterAction::moveAround(const stdsptr<eCharActFunc>& finishAct,
                                   const int time) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto t = c->tile();
    const int tx = t->x();
    const int ty = t->y();
    const auto a = e::make_shared<eMoveAroundAction>(
                       c, tx, ty, eWalkableObject::sCreateDefault());
    a->setFinishAction(finishAct);
    a->setFailAction(finishAct);
    a->setMaxDistance(10);
    a->setTime(time);
    setCurrentAction(a);
}

void eGodMonsterAction::goToTarget(const eHeatGetters::eHeatGetter hg,
                                   const stdsptr<eFindFailFunc>& findFailFunc,
                                   const stdsptr<eObsticleHandler>& oh,
                                   const eTileDistance& tileDistance,
                                   const stdsptr<eWalkableObject>& pathFindWalkable,
                                   const stdsptr<eWalkableObject>& moveWalkable) {
    const auto c = character();
    const stdptr<eGodMonsterAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto hmFinish = [tptr, this, cptr,
                          c, findFailFunc, oh,
                          tileDistance,
                          pathFindWalkable,
                          moveWalkable](eHeatMap& map) {
        if(!tptr || !cptr) return;
        eHeatMapDivisor divisor(map);
        divisor.divide(10);
        int tx;
        int ty;
        const bool r = divisor.randomHeatTile(tx, ty);
        if(r) {
            auto& board = c->getBoard();
            const auto tile = eTileHelper::closestRoad(tx, ty, board);
            goToTile(tile, findFailFunc, oh, tileDistance,
                     pathFindWalkable, moveWalkable);
        } else {
            setCurrentAction(nullptr);
        }
    };
    const auto task = new eHeatMapTask(hg, hmFinish);
    auto& board = c->getBoard();
    auto& tp = board.threadPool();
    tp.queueTask(task);
    wait();
}

void eGodMonsterAction::goToTile(
        eTile* const tile,
        const stdsptr<eFindFailFunc>& findFailFunc,
        const stdsptr<eObsticleHandler>& oh,
        const eTileDistance& tileDistance,
        const stdsptr<eWalkableObject>& pathFindWalkable,
        const stdsptr<eWalkableObject>& moveWalkable) {
    const auto c = character();
    if(!tile || !c) return setCurrentAction(nullptr);
    auto& board = c->getBoard();
    const auto ff = std::make_shared<eGMA_goToTargetFail>(
                        board, tile, findFailFunc);
    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(ff);
    a->setObsticleHandler(oh);
    a->setTileDistance(tileDistance);
    a->start(tile, pathFindWalkable, moveWalkable);
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);
}

void eGodMonsterAction::spawnMissile(const eCharacterActionType at,
                                     const eCharacterType chart,
                                     const int attackTime,
                                     eTile* const target,
                                     const stdsptr<eCharActFunc>& playSound,
                                     const stdsptr<eGodAct>& hitAct,
                                     const stdsptr<eCharActFunc>& finishAttackA) {
    const stdptr<eGodMonsterAction> tptr(this);
    const auto finish = std::make_shared<eGMA_spawnMissileFinish>(
                            board(), character(),
                            at, chart, target, playSound,
                            hitAct, finishAttackA);
    const auto c = character();
    c->setActionType(at);
    {
        const auto ct = c->tile();
        const int tx = ct->x();
        const int ty = ct->y();
        const int ttx = target->x();
        const int tty = target->y();
        const double dx = ttx - tx;
        const double dy = tty - ty;

        const vec2d angleLine{dx, dy};
        const double a = angleLine.angle();
        const auto o = sAngleOrientation(a);
        c->setOrientation(o);
    }

    if(playSound) playSound->call();

    const auto a = e::make_shared<eWaitAction>(c);
    a->setFailAction(finish);
    a->setFinishAction(finish);
    a->setTime(attackTime);
    setCurrentAction(a);
}

void eGodMonsterAction::spawnMultipleMissiles(
          const eCharacterActionType at,
          const eCharacterType ct,
          const int attackTime,
          eTile* const target,
          const stdsptr<eCharActFunc>& playSound,
          const stdsptr<eGodAct>& playHitSound,
          const stdsptr<eCharActFunc>& finishA,
          const int nMissiles) {
    if(nMissiles <= 0) {
        if(finishA) finishA->call();
        return;
    }
    stdsptr<eCharActFunc> finishAA;
    if(nMissiles == 1) {
        finishAA = finishA;
    } else {
        finishAA = std::make_shared<eGMA_spawnMultipleMissilesFinish>(
                       board(), this, at, ct, attackTime,
                       target, playSound, playHitSound,
                       finishA, nMissiles);
    }
    spawnMissile(at, ct, attackTime, target,
                 playSound, playHitSound, finishAA);
}

void eGodMonsterAction::spawnTimedMissiles(
        const eCharacterActionType at,
        const eCharacterType ct,
        const int attackTime,
        eTile* const target,
        const stdsptr<eCharActFunc>& playSound,
        const stdsptr<eGodAct>& playHitSound,
        const stdsptr<eCharActFunc>& finishA,
        const int time) {
    const int n = std::round(double(time)/attackTime);
    spawnMultipleMissiles(at, ct, attackTime, target,
                          playSound, playHitSound,
                          finishA, n);
}

void eGodMonsterAction::patrol(
        const stdsptr<eCharActFunc>& finishAct,
        const int dist) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto failAct = std::make_shared<eGMA_patrolFail>(
                board(), this, finishAct, dist);
    const auto a = e::make_shared<ePatrolMoveAction>(c);
    a->setFailAction(failAct);
    a->setFinishAction(finishAct);
    a->setMaxWalkDistance(dist);
    setCurrentAction(a);
}

void eGodMonsterAction::goToNearestRoad(
        const stdsptr<eCharActFunc>& finishAct,
        const int dist) {
    const auto c = character();
    const auto t = c->tile();
    if(t->hasRoad()) return;
    const auto cr = eTileHelper::closestRoad(t->x(), t->y(), board());
    if(cr) {
        const auto fail = std::make_shared<eGMA_patrolFailFail>(
                              board(), this, finishAct);
        const auto finish = std::make_shared<eGMA_patrolFailFinish>(
                                board(), this, finishAct, dist);
        const auto a = e::make_shared<eMoveToAction>(c);
        a->setFailAction(fail);
        a->setFinishAction(finish);
        a->start(cr);
        setCurrentAction(a);
    } else {
        moveAround(finishAct, 15000);
    }
}

void eGodMonsterAction::pauseAction() {
    const auto ca = currentAction();
    if(!ca) return;
    auto& p = mPausedActions.emplace_back();
    p.fA = ca->ref<eCharacterAction>();
    const auto c = character();
    p.fAt = c->actionType();
    p.fO = c->orientation();
}

void eGodMonsterAction::resumeAction() {
    if(mPausedActions.empty()) return;
    const auto p = mPausedActions.back();
    mPausedActions.pop_back();
    setCurrentAction(p.fA);
    const auto c = character();
    c->setActionType(p.fAt);
}

void eGodMonsterAction::read(eReadStream& src) {
    eComplexAction::read(src);
    int s;
    src >> s;
    for(int i = 0; i < s; i++) {
        auto& a = mPausedActions.emplace_back();
        src >> a.fAt;
        bool hasAction;
        src >> hasAction;
        if(hasAction) {
            eCharActionType type;
            src >> type;
            a.fA = eCharacterAction::sCreate(character(),
                                             type);
            a.fA->read(src);
        }
        src >> a.fO;
    }
}

void eGodMonsterAction::write(eWriteStream& dst) const {
    eComplexAction::write(dst);
    dst << mPausedActions.size();
    for(const auto& a : mPausedActions) {
        dst << a.fAt;
        dst << (a.fA != nullptr);
        if(a.fA) {
            dst << a.fA->type();
            a.fA->write(dst);
        }
        dst << a.fO;
    }
}

stdsptr<eFindFailFunc> eFindFailFunc::sCreate(
        eGameBoard& board,
        const eFindFailFuncType type) {
    switch(type) {
    case eFindFailFuncType::teleport:
        return std::make_shared<eTeleportFindFailFunc>(board);
    case eFindFailFuncType::teleport2:
        return std::make_shared<eGoToTargetTeleport>(board);
    case eFindFailFuncType::tryAgain:
        return std::make_shared<eGoToTargetTryAgain>(board);
    }
    return nullptr;
}
