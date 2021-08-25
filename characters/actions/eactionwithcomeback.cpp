#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "characters/actions/ewaitaction.h"
#include "engine/ethreadpool.h"
#include "epathfindtask.h"

eActionWithComeback::eActionWithComeback(
        eCharacter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction) {
    const auto t = c->tile();
    if(t) {
        mStartX = t->x();
        mStartY = t->y();
    }
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
    const stdptr<eActionWithComeback> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [tptr, c, walkable, failFunc](
                            const std::vector<eOrientation>& path) {
        if(!tptr) return;
        const auto finishAction = [tptr]() {
            if(tptr) tptr->setState(eCharacterActionState::finished);
        };

        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, walkable,
                            failFunc, finishAction);
        tptr->setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));
}
