#include "ecollectaction.h"

#include "engine/egameboard.h"
#include "esounds.h"

eCollectAction::eCollectAction(eResourceCollectorBase* const c,
                               const eTranformFunc& tf,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mCharacter(c), mTile(c->tile()),
    mTransFunc(tf) {}

void eCollectAction::increment(const int by) {
    mTime += by;
    mSoundTime += sqrt(by);
    if(mSoundTime > 100) {
        mSoundTime = 0;
        const auto c = character();
        const auto cType = c->type();
        auto& board = c->getBoard();
        board.ifVisible(c->tile(), [cType]() {
            if(cType == eCharacterType::marbleMiner) {
                eSounds::playStoneCutterSound();
            } else if(cType == eCharacterType::bronzeMiner) {
                eSounds::playCopperMinerSound();
            } else if(cType == eCharacterType::silverMiner) {
                eSounds::playSilverMinerSound();
            } else if(cType == eCharacterType::lumberjack) {
                eSounds::playTreeCutterSound();
            }
        });
    }
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
        mTime = 0;
        setState(eCharacterActionState::finished);
    }
}
