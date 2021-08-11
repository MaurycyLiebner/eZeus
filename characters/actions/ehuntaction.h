#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "eactionwithcomeback.h"

#include "characters/ehunter.h"

class eHuntAction : public eActionWithComeback {
public:
    using eHasResource = std::function<bool(eTile*)>;
    eHuntAction(eHunter* const c,
                const eHasResource& hr,
                const eAction& failAction,
                const eAction& finishAction);

    void increment(const int by);

    void resume();
private:
    bool findResource();
    bool collect();
    bool goBack2();

    const eHasResource mHasResource;
    eHunter* const mCharacter;
    eResourceCollectorAction mAction{0};
};

#endif // EHUNTACTION_H
