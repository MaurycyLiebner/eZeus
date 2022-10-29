#include "egodmonsteraction.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "emovetoaction.h"
#include "engine/egameboard.h"
#include "eiteratesquare.h"

#include "missiles/egodmissile.h"

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
                                   const eFindFailFunc& findFailFunc,
                                   const eObsticleHandler& oh) {
    const auto c = character();
    const stdptr<eGodMonsterAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto hmFinish = [tptr, this, cptr,
                          c, findFailFunc, oh](eHeatMap& map) {
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
            a->setObsticleHandler(oh);
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

void eGodMonsterAction::spawnMissile(const eCharacterActionType at,
                                     const eTexPtr tex,
                                     const int attackTime,
                                     eTile* const target,
                                     const eFunc& playSound,
                                     const eFunc& finishMissileA,
                                     const eFunc& finishAttackA) {
    const stdptr<eGodMonsterAction> tptr(this);
    const auto finish = [tptr, this, tex, target,
                        finishMissileA, finishAttackA, at]() {
        if(!tptr) return;
        const auto c = character();
        const auto charType = c->type();
        const auto ct = c->tile();
        const int tx = ct->x();
        const int ty = ct->y();
        const int ttx = target->x();
        const int tty = target->y();
        auto& brd = c->getBoard();
        double h;
        if(at == eCharacterActionType::fight) {
            switch(charType) {
            case eCharacterType::apollo:
                h = -0.5;
                break;
            default:
                h = 0;
                break;
            }
        } else {
            h = 0;
        }

        const auto m = eMissile::sCreate<eGodMissile>(
                           brd, tx, ty, h,
                           ttx, tty, h, 0);
        m->setTexture(tex);

        m->setFinishAction(finishMissileA);

        if(finishAttackA) finishAttackA();
    };
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
        const double inc = 360./8.;
        const double aa = a + 90;
        const double aaa = aa > 360. ? aa - 360. : aa;
        const int oi = int(std::floor(aaa/inc)) % 8;
        const auto o = static_cast<eOrientation>(oi);
        c->setOrientation(o);
    }
    const auto a = e::make_shared<eWaitAction>(c, finish, finish);
    a->setTime(attackTime);
    setCurrentAction(a);

    if(playSound) playSound();
}

void eGodMonsterAction::spawnMultipleMissiles(
          const eCharacterActionType at,
          const eTexPtr tex,
          const int attackTime,
          eTile* const target,
          const eFunc& playSound,
          const eFunc& finishA,
          const int nMissiles) {
    if(nMissiles <= 0) {
        finishA();
        return;
    }
    eFunc finishAA;
    if(nMissiles == 1) {
        finishAA = finishA;
    } else {
        const stdptr<eGodMonsterAction> tptr(this);
        finishAA = [tptr, this, at, tex, attackTime,
                   target, playSound, finishA, nMissiles]() {
            if(!tptr) return;
            spawnMultipleMissiles(at, tex, attackTime, target,
                                  playSound, finishA, nMissiles - 1);
        };
    }
    spawnMissile(at, tex, attackTime, target,
                 playSound, nullptr, finishAA);
}

void eGodMonsterAction::spawnTimedMissiles(
        const eCharacterActionType at,
        const eTexPtr tex,
        const int attackTime,
        eTile* const target,
        const eFunc& playSound,
        const eFunc& finishA,
        const int time) {
    const int n = std::round(double(time)/attackTime);
    spawnMultipleMissiles(at, tex, attackTime, target,
                          playSound, finishA, n);
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