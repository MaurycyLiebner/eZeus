#include "ebuildaction.h"

#include "engine/egameboard.h"
#include "audio/esounds.h"
#include "buildings/sanctuaries/esanctbuilding.h"

eBuildAction::eBuildAction(eCharacter* const c) :
    eCharacterAction(c, eCharActionType::buildAction) {}

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

void eBuildAction::read(eReadStream& src) {
    eCharacterAction::read(src);
    src >> mSoundTime;
    src >> mTime;
}

void eBuildAction::write(eWriteStream& dst) const {
    eCharacterAction::write(dst);
    dst << mSoundTime;
    dst << mTime;
}
