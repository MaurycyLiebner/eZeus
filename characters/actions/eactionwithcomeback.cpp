#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "emovetoaction.h"

eActionWithComeback::eActionWithComeback(
        eCharacter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mStartTile(c->tile()) {}

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

    const auto a = e::make_shared<eMoveToAction>(c, failFunc, [](){});
    a->setFindFailAction([tptr, this]() {
        if(!tptr) return;
        mGoBackFail = true;
    });
    a->start(finalTile, walkable);
    setCurrentAction(a);
}

void eActionWithComeback::goBack(eBuilding* const b,
                                 const eWalkable& walkable) {
    const auto rect = b->tileRect();
    eActionWithComeback::goBack([rect, walkable](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return walkable(t);
    });
}

void eActionWithComeback::teleportDecision() {
    const auto c = character();

    c->changeTile(mStartTile);
    c->setX(0.5);
    c->setY(0.5);
}
