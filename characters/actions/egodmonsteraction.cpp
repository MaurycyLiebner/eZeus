#include "egodmonsteraction.h"

#include "emovearoundaction.h"
#include "emovetoaction.h"
#include "engine/egameboard.h"
#include "eiteratesquare.h"

eTile* eGodMonsterAction::closestRoad(const int rdx, const int rdy) const {
    const auto c = character();
    auto& board = c->getBoard();
    eTile* roadTile = nullptr;
    eTile* plainTile = nullptr;
    const auto prcsTile = [&](const int i, const int j) {
        const int tx = rdx + i;
        const int ty = rdy + j;
        const auto tt = board.dtile(tx, ty);
        if(!tt) return false;
        if(tt->hasRoad()) {
            roadTile = tt;
            return true;
        } else if(!plainTile && tt->walkable()) {
            plainTile = tt;
        }
        return false;
    };

    for(int k = 0; k < 1000; k++) {
        eIterateSquare::iterateSquare(k, prcsTile, 1);
        if(roadTile) break;
    }

    const auto tile = roadTile ? roadTile : plainTile;
    return tile;
}

void eGodMonsterAction::moveAround(const eAction& finishAct, const int time) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto t = c->tile();
    const int tx = t->x();
    const int ty = t->y();
    const auto a = e::make_shared<eMoveAroundAction>(
                       c, finishAct, finishAct, tx, ty,
                       eMoveAroundAction::sDefaultWalkable);
    a->setTime(time);
    setCurrentAction(a);
}

void eGodMonsterAction::goToTarget(const eHeatGetters::eHeatGetter hg,
                                   const eFindFailFunc& findFailFunc) {
    const auto c = character();
    const stdptr<eGodMonsterAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto hmFinish = [tptr, this, cptr,
                          c, findFailFunc](eHeatMap& map) {
        if(!tptr || !cptr) return;
        eHeatMapDivisor divisor(map);
        divisor.divide(10);
        int tx;
        int ty;
        const bool r = divisor.randomHeatTile(tx, ty);
        if(r) {
            const auto tile = closestRoad(tx, ty);
            if(!tile) return setCurrentAction(nullptr);
            const auto ff = [tile, findFailFunc]() {
                findFailFunc(tile);
            };
            const auto a = e::make_shared<eMoveToAction>(
                               c, ff, [](){});
            a->setFindFailAction(ff);
            a->start(tile);
            setCurrentAction(a);
            c->setActionType(eCharacterActionType::walk);
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
