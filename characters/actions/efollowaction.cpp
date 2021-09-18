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
    if(!mTiles.empty() && ft == mTiles.back().fTile) return;
    mTiles.push({ft, mFollow->orientation()});
    const int tmax = mTiles.size();
    const auto pn = mTiles.front();
    if(tmax > mDistance) mTiles.pop();
    const auto c = character();
    c->changeTile(pn.fTile);
    c->setOrientation(pn.fO);
}
