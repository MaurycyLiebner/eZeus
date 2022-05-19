#ifndef EBUILDACTION_H
#define EBUILDACTION_H

#include "echaracteraction.h"

#include "characters/eartisan.h"

class eBuildAction : public eCharacterAction {
public:
    eBuildAction(eArtisan* const c,
                 const eAction& failAction,
                 const eAction& finishAction);


    void increment(const int by);
private:
    int mSoundTime = 0;
    int mTime = 0;
    eArtisan* const mCharacter;
    eTile* const mTile;
};

#endif // EBUILDACTION_H
