#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "emovetoaction.h"

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

    const int startX = mStartX;
    const int startY = mStartY;
    const auto finalTile = [startX, startY](eTileBase* const t) {
        return t->x() == startX && t->y() == startY;
    };
    const stdptr<eActionWithComeback> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    const auto finishAction = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::finished);
    };

    const auto a = e::make_shared<eMoveToAction>(c, failFunc, finishAction);
    a->start(finalTile, walkable);
    setCurrentAction(a);
}
