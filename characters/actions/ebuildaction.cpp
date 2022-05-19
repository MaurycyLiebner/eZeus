#include "ebuildaction.h"

#include "engine/egameboard.h"
#include "esounds.h"
#include "buildings/sanctuaries/esanctbuilding.h"

eBuildAction::eBuildAction(eArtisan* const c,
                           const eAction& failAction,
                           const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mCharacter(c), mTile(c->tile()) {}

void eBuildAction::increment(const int by) {
    mTime += by;
    mSoundTime += sqrt(by);
    if(mSoundTime > 100) {
        mSoundTime = 0;
        const auto c = character();
        auto& board = c->getBoard();
        board.ifVisible(c->tile(), []() {
            eSounds::playArtisanSound();
        });
    }
    if(mTime > 2000) {
        setState(eCharacterActionState::finished);
    }
}
