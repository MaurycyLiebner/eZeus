#include "efollowaction.h"

#include "../echaracter.h"

#include "engine/emainthreadpathfinder.h"

bool allWalkable(eTileBase*) {
    return true;
}

eFollowAction::eFollowAction(eCharacter* const f,
                             eCharacter* const c,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eMoveAction(c, allWalkable, failAction, finishAction),
    mFollow(f) {}

eCharacterActionState eFollowAction::nextTurn(eOrientation& t) {
    if(!mFollow) return eCharacterActionState::finished;
    const auto ft = mFollow->tile();
    if(!ft) return eCharacterActionState::finished;
    const auto c = character();

    const auto pause = [&]() {
        t = c->orientation();
        mPaused = true;
        mPauseTile = ft;
    };
    if(c->tile() == ft) {
        pause();
    } else {
        const auto finish = [&](eTile* const tile) {
            const int tx = tile->x();
            const int ty = tile->y();
            return tx == ft->x() && ty == ft->y();
        };
        std::vector<eOrientation> path;
        eMainThreadPathFinder pf(allWalkable, finish);
        pf.findPath(c->tile(), 5, path, false);
        if(path.empty()) {
            pause();
        } else {
            t = path.back();
        }
    }
    return eCharacterActionState::running;
}

void eFollowAction::increment(const int by) {
    if(mPaused) {
        if(mPauseTile == mFollow->tile()) return;
        mPaused = false;
        eMoveAction::nextTurn();
    }
    return eMoveAction::increment(by);
}
