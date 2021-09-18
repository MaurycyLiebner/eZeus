#include "efollowaction.h"

#include "../echaracter.h"

#include "engine/emainthreadpathfinder.h"

bool allWalkable(eTileBase* const tile) {
    return tile->hasRoad();
    return tile->walkable();
}

eFollowAction::eFollowAction(eCharacter* const f,
                             eCharacter* const c,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mFollow(f) {
    c->setActionType(eCharacterActionType::stand);
}

void eFollowAction::setDistance(const int d) {
    mDistance = d;
}

void eFollowAction::increment(const int by) {
    (void)by;
    if(!mFollow) return setState(eCharacterActionState::finished);
    const auto ft = mFollow->tile();
    if(!ft) return setState(eCharacterActionState::finished);
    const auto c = character();
    if(!mTiles.empty()) {
        auto& b = mTiles.back();
        if(ft == b.fTile) {
            b.fO = mFollow->orientation();
            return;
        }
    }
    mTiles.push({ft, mFollow->orientation()});
    const int nt = mTiles.size();
    if(nt < mDistance + 1) return;
    if(nt > mDistance + 1) mTiles.pop();
    const auto pn = mTiles.front();
    c->setActionType(eCharacterActionType::walk);
    c->changeTile(pn.fTile);
    c->setOrientation(pn.fO);
    c->setX(0.5);
    c->setY(0.5);
    mPos = 1;
}
