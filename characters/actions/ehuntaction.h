#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "eactionwithcomeback.h"

#include "characters/ehunter.h"

class eHuntAction : public eActionWithComeback {
public:
    using eHasResource = std::function<bool(eTile*)>;
    using eHasCollectableResource = std::function<bool(eTile*)>;
    eHuntAction(eHunter* const c,
                const eHasResource& hr,
                const eHasCollectableResource& hcr,
                const eAction& failAction,
                const eAction& finishAction);

    void increment(const int by);

    void resume();
private:
    bool findResource();
    bool collect();
    bool goBack2();

    const eHasResource mHasResource;
    const eHasCollectableResource mHasCollectableResource;
    eHunter* const mCharacter;
};

#endif // EHUNTACTION_H
