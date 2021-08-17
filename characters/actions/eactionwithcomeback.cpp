#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "engine/epathfinder.h"

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

bool eActionWithComeback::goBack(const eWalkable& walkable) {
    const auto c = character();
    const auto t = c->tile();

    const auto finalTile = [this](eTileBase* const t) {
        return t->x() == mStartX && t->y() == mStartY;
    };
    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        setState(eCharacterActionState::finished);
    };

    const auto pf0 = ePathFinder(t, walkable, finalTile);
    std::vector<eOrientation> path0;
    const bool r0 = pf0.findPath(100, path0, false);
    if(r0) {
        const auto a  = new eMovePathAction(c, path0, walkable,
                                            failAction, finishAction);
        setCurrentAction(a);
        return true;
    }
    setState(eCharacterActionState::failed);
    return false;
}
