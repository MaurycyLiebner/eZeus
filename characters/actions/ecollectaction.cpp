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
    if(mTime > 100) {
        mTile->decResource(by);
        mCharacter->incCollected(by);
        const bool noResLeft = mTile->resource() <= 0;
        if(noResLeft) mTransFunc(mTile);
        if(noResLeft || mCharacter->collected() >= 1) {
            setState(eCharacterActionState::finished);
        }
        mTime = 0;
    }
}
