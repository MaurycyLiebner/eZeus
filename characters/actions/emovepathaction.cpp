#include "emovepathaction.h"

#include "characters/echaracter.h"

eMovePathAction::eMovePathAction(eCharacter* const c,
                                 const std::vector<eOrientation>& path,
                                 const eTileWalkable& tileWalkable,
                                 const eAction& failAction,
                                 const eAction& finishAction) :
    eMoveAction(c, tileWalkable, failAction, finishAction),
    mTurns(path) {
}

eCharacterActionState eMovePathAction::nextTurn(eOrientation& turn) {
    if(mTurns.empty()) return eCharacterActionState::finished;
    turn = mTurns.back();
    mTurns.pop_back();

    const auto t = character()->tile();
    const auto tt = t->neighbour(turn);
    if(!tt) return eCharacterActionState::failed;
    return eCharacterActionState::running;
}
