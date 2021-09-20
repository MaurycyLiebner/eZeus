#ifndef ECOLLECTACTION_H
#define ECOLLECTACTION_H

#include "echaracteraction.h"

#include "characters/eresourcecollector.h"

class eCollectAction : public eCharacterAction {
public:
    using eTranformFunc = std::function<void(eTile*)>;
    eCollectAction(
            eResourceCollector* const c,
            const eTranformFunc& tf,
            const eAction& failAction,
            const eAction& finishAction);


    void increment(const int by);
private:
    int mSoundTime = 0;
    int mTime = 0;
    eResourceCollector* const mCharacter;
    eTile* const mTile;
    const eTranformFunc mTransFunc;
};

#endif // ECOLLECTACTION_H
