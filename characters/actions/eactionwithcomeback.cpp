#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "characters/actions/ewaitaction.h"
#include "engine/ethreadpool.h"
#include "epathfindtask.h"

eActionWithComeback::eActionWithComeback(
        eCharacter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction) {
    const auto t = c->tile();
    if(t) {
        mStartX = t->x();
        mStartY = t->y();
    }
}

eActionWithComeback::~eActionWithComeback() {
    setCurrentAction(nullptr);
}

void eActionWithComeback::increment(const int by) {
    if(mCurrentAction) mCurrentAction->increment(by);
}

void eActionWithComeback::setCurrentAction(eCharacterAction* const a) {
    if(mCurrentAction) delete mCurrentAction;
    mCurrentAction = a;
}

void eActionWithComeback::goBack(const eWalkable& walkable) {
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const int startX = mStartX;
    const int startY = mStartY;
    const auto finalTile = [startX, startY](eThreadTile* const t) {
        return t->x() == startX && t->y() == startY;
    };
    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [this, c, walkable, failFunc](
                            const std::vector<eOrientation>& path) {
        const auto finishAction = [this]() {
            setState(eCharacterActionState::finished);
        };

        const auto a  = new eMovePathAction(c, path, walkable,
                                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(new eWaitAction(c, []() {}, []() {}));
}
