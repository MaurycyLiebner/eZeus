#include "efirefighteraction.h"

#include "../echaracter.h"
#include "engine/egameboard.h"
#include "engine/thread/ethreadboard.h"
#include "engine/ethreadpool.h"
#include "epathfindtask.h"
#include "ewaitaction.h"

eFireFighterAction::eFireFighterAction(
        eCharacter* const c,
        const std::vector<ePatrolGuide>& guides,
        const eAction& failAction,
        const eAction& finishAction) :
    ePatrolAction(c, guides, failAction, finishAction) {

}

void eFireFighterAction::increment(const int by) {
    const int fireCheckInc = 200;
    mFireCheck += by;
    if(mFireCheck > fireCheckInc) {
        mFireCheck = 0;
        lookForFire();
    }
    ePatrolAction::increment(by);
}

bool eFireFighterAction::lookForFire() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto tileWalkable = [](eTileBase* const t) {
        return t->walkable() || t->onFire();
    };
    const auto failFunc = []() {};
    const auto finishFunc = [this, c, tileWalkable, failFunc](
                            std::vector<eOrientation> path) {
        const auto o = path.back();
        path.pop_back();
        const auto finishAction = [this, c, o]() {
            const auto tile = c->tile();
            const auto n = tile->neighbour<eTile>(o);
            if(n && n->onFire()) {
                c->setOrientation(o);
                putOutFire(n);
            } else patrol();
        };

        const auto a  = new eMovePathAction(c, path, tileWalkable,
                                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto onFire = [](eTileBase* const tile) {
        return tile->onFire();
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       onFire, finishFunc,
                                       failFunc);
    tp->queueTask(pft);

    return true;
}

void eFireFighterAction::putOutFire(eTile* const tile) {
    const auto c = character();
    c->setActionType(eCharacterActionType::fight);
    const auto finish = [this, tile]() {
        tile->setOnFire(false);
        lookForFire();
    };
    const auto a = new eWaitAction(c, []() {}, finish);
    setCurrentAction(a);
}
