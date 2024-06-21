#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "emovetoaction.h"

eActionWithComeback::eActionWithComeback(
        eCharacter* const c,
        eTile* const startTile,
        const eCharActionType type) :
    eComplexAction(c, type),
    mStartTile(startTile) {}

eActionWithComeback::eActionWithComeback(eCharacter* const c,
                                         const eCharActionType type) :
    eActionWithComeback(c, c->tile(), type) {}

bool eActionWithComeback::decide() {
    if(mGoBackFail) {
        mGoBackFail = false;
        teleportDecision();
        return true;
    }
    return false;
}

void eActionWithComeback::read(eReadStream& src) {
    eComplexAction::read(src);
    mStartTile = src.readTile(board());
    src >> mGoBackRect;
    src >> mFinishOnComeback;
    src >> mDefaultTry;
    src >> mGoBackFail;
}

void eActionWithComeback::write(eWriteStream& dst) const {
    eComplexAction::write(dst);
    dst.writeTile(mStartTile);
    dst << mGoBackRect;
    dst << mFinishOnComeback;
    dst << mDefaultTry;
    dst << mGoBackFail;
}

void eActionWithComeback::goBack(stdsptr<eWalkableObject> walkable) {
    const auto c = character();
    const auto ct = c->tile();
    if(ct == mStartTile) return teleportDecision();

    const int startX = mStartTile->x();
    const int startY = mStartTile->y();
    const auto finalTile = [startX, startY](eTileBase* const t) {
        return t->x() == startX && t->y() == startY;
    };
    const auto failFunc = std::make_shared<eAWC_goBackFail>(board(), this, walkable);

    stdsptr<eAWC_goBackFinish> finishFunc;
    if(mFinishOnComeback) {
        finishFunc = std::make_shared<eAWC_goBackFinish>(board(), this);
    }
    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFinishAction(finishFunc);
    a->setFailAction(failFunc);

    const stdptr<eActionWithComeback> tptr(this);
    a->setFindFailAction([tptr, this, walkable]() {
        if(!tptr) return;
        if(mDefaultTry) {
            mGoBackFail = true;
        } else {
            mDefaultTry = true;
            stdsptr<eWalkableObject> w;
            if(SDL_RectEmpty(&mGoBackRect)) {
                w = eWalkableObject::sCreateDefault();
            } else {
                w = eWalkableObject::sCreateRect(
                        mGoBackRect, eWalkableObject::sCreateDefault());
            }
            goBack(w);
        }
    });
    if(const auto ub = mStartTile->underBuilding()) {
        walkable = eWalkableObject::sCreateRect(ub, walkable);
    }
    a->start(finalTile, walkable);
    setCurrentAction(a);
}

void eActionWithComeback::goBack(eBuilding* const b,
                                 const stdsptr<eWalkableObject>& walkable) {
    const auto rect = b->tileRect();
    goBack(rect, walkable);
}

void eActionWithComeback::goBack(const SDL_Rect& rect,
                                 const stdsptr<eWalkableObject>& walkable) {
    mGoBackRect = rect;
    const auto w = eWalkableObject::sCreateRect(rect, walkable);
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
