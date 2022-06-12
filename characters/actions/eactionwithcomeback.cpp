#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "emovetoaction.h"

eActionWithComeback::eActionWithComeback(
        eCharacter* const c,
        eTile* const startTile,
        const eAction& failAction,
        const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mStartTile(startTile) {}

eActionWithComeback::eActionWithComeback(
        eCharacter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, c->tile(), failAction, finishAction) {}

bool eActionWithComeback::decide() {
    if(mGoBackFail) {
        mGoBackFail = false;
        teleportDecision();
        return true;
    }
    return false;
}

void eActionWithComeback::goBack(const eWalkable& walkable) {
    const auto c = character();

    const int startX = mStartTile->x();
    const int startY = mStartTile->y();
    const auto finalTile = [startX, startY](eTileBase* const t) {
        return t->x() == startX && t->y() == startY;
    };
    const stdptr<eActionWithComeback> tptr(this);
    const auto failFunc = [tptr, this, walkable]() {
        if(!tptr) return;
        goBack(walkable);
    };

    eAction finishFunc;
    if(mFinishOnComeback) {
        finishFunc = [tptr, this]() {
            if(!tptr) return;
            setState(eCharacterActionState::finished);
        };
    }
    const auto a = e::make_shared<eMoveToAction>(c, failFunc, finishFunc);
    a->setFindFailAction([tptr, this, walkable]() {
        if(!tptr) return;
        if(mDefaultTry) {
            mGoBackFail = true;
        } else {
            mDefaultTry = true;
            goBack(eWalkableHelpers::sDefaultWalkable);
        }
    });
    a->start(finalTile, walkable);
    setCurrentAction(a);
}

void eActionWithComeback::goBack(eBuilding* const b,
                                 const eWalkable& walkable) {
    const auto rect = b->tileRect();
    goBack(rect, walkable);
}

void eActionWithComeback::goBack(const SDL_Rect& rect,
                                 const eWalkable& walkable) {
    const auto w = eWalkableHelpers::sBuildingWalkable(rect, walkable);
    eActionWithComeback::goBack(w);
}

void eActionWithComeback::teleportDecision() {
    const auto c = character();

    c->changeTile(mStartTile);
    c->setX(0.5);
    c->setY(0.5);

    if(mFinishOnComeback) {
        setState(eCharacterActionState::finished);
    }
}
