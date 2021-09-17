#include "ecollectaction.h"

eCollectAction::eCollectAction(eResourceCollector* const c,
                               const eTranformFunc& tf,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mCharacter(c), mTile(c->tile()),
    mTransFunc(tf) {}

void eCollectAction::increment(const int by) {
    mTime += by;
    if(mTime > 6000) {
        const auto terr = mTile->terrain();
        if(terr == eTerrain::marble) {
            mTile->decResource(100);
        } else {
            mTile->decResource(1);
        }
        mCharacter->incCollected(1);
        const bool noResLeft = mTile->resource() <= 0;
        if(noResLeft) mTransFunc(mTile);
        setState(eCharacterActionState::finished);
        mTime = 0;
    }
}
