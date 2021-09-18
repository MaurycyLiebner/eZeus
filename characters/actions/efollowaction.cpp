#include "efollowaction.h"

#include "../echaracter.h"

#include "engine/emainthreadpathfinder.h"

#include "emovepathaction.h"

eFollowAction::eFollowAction(eCharacter* const f,
                             eCharacter* const c,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mFollow(f) {
    c->setActionType(eCharacterActionType::stand);
}

void eFollowAction::setDistance(const int d) {
    mDistance = d;
}

void eFollowAction::increment(const int by) {
    if(!mFollow) return setState(eCharacterActionState::finished);
    const auto ft = mFollow->tile();
    if(!ft) return setState(eCharacterActionState::finished);
    const auto c = character();
    if(!mTiles.empty()) {
        auto& b = mTiles.back();
        if(ft == b.fTile) {
            b.fO = mFollow->orientation();
            eComplexAction::increment(by);
            return;
        }
    }
    mTiles.push({ft, mFollow->orientation()});
    const int nt = mTiles.size();
    if(nt < mDistance + 2) return;
    if(nt > mDistance + 2) mTiles.pop();
    const auto pn = mTiles.front();
    c->setActionType(eCharacterActionType::walk);
    c->changeTile(pn.fTile);
    c->setOrientation(pn.fO);
    const auto walkable = [](eTileBase* const) { return true; };
    const std::vector<eOrientation> path = {pn.fO};
    const auto a = e::make_shared<eMovePathAction>(
                       c, path, walkable, []() {}, []() {});
    setCurrentAction(a);
    eComplexAction::increment(by);
}
