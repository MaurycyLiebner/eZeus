#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "echaracteraction.h"

#include "characters/eresourcecollector.h"

class eHuntAction : public eCharacterAction {
public:
    eHuntAction(eResourceCollector* const c,
                const eAction& failAction,
                const eAction& finishAction);


    void increment(const int by);
private:
    int mTime = 0;
    eResourceCollector* const mCharacter;
    eTile* const mTile;
};

#endif // EHUNTACTION_H
