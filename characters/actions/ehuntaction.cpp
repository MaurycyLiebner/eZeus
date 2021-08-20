#include "ehuntaction.h"

#include "engine/epathfinder.h"

#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"

eHuntAction::eHuntAction(
        eHunter* const c,
        const eHasResource& hr,
        const eHasCollectableResource& hcr,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mHasCollectableResource(hcr),
    mCharacter(c) {}

void eHuntAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eHuntAction::resume() {
    eActionWithComeback::resume();
    const auto tile = mCharacter->tile();
    if(mHasCollectableResource(tile)) collect();
}

bool eHuntAction::findResource() {
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto tileWalkable = [](eTileBase* const t) {
        return t->walkable();
    };
    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [this, c, tileWalkable, failFunc](
                            const std::vector<eOrientation>& path) {
        const auto finishAction = [this, c]() {
            const auto tile = c->tile();
            if(mHasCollectableResource(tile)) collect();
            else findResource();
        };

        const auto a  = new eMovePathAction(c, path, tileWalkable,
                                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       mHasResource, finishFunc,
                                       failFunc, 50);
    tp->queueTask(pft);

    setCurrentAction(new eWaitAction(c, []() {}, []() {}));

    return true;
}

bool eHuntAction::collect() {
    mCharacter->incCollected(1);
    goBack2();
    return true;
}

void eHuntAction::goBack2() {
    mCharacter->setActionType(eCharacterActionType::carry);
    eActionWithComeback::goBack([](eTileBase* const t) {
        return t->walkable();
    });
}
