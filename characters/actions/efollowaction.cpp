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
    if(mPaused) {
        if(mPauseTile == mFollow->tile()) return;
        mPaused = false;
    }
    if(!mFollow) return setState(eCharacterActionState::finished);
    const auto ft = mFollow->tile();
    if(!ft) return setState(eCharacterActionState::finished);
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);

    const auto pause = [&]() {
        mPaused = true;
        mPauseTile = ft;
        c->setActionType(eCharacterActionType::stand);
    };
    const auto cTile = c->tile();
    if(eTileBase::sDistance(cTile, ft) < mDistance) {
        pause();
    } else {
        const auto finish = [&](eTile* const tile) {
            const int tx = tile->x();
            const int ty = tile->y();
            return tx == ft->x() && ty == ft->y();
        };
        std::vector<eOrientation> path;
        eMainThreadPathFinder pf(allWalkable, finish);
        pf.findPath(cTile, 10, path, false);
        eOrientation oo{mFollow->orientation()};
        auto tt = ft;
        const int iMax = path.size();
        for(int i = 0; i < mDistance && i < iMax; i++) {
            oo = path[i];
            tt = tt->neighbour<eTile>(!oo);
        }

        if(tt == cTile) {
            pause();
        } else {
            c->changeTile(tt);
            c->setOrientation(oo);
        }
    }
}
