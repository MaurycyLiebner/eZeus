#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "eactionwithcomeback.h"

#include "characters/ehunter.h"

class eHuntingLodge;

class eHuntAction : public eActionWithComeback {
public:
    eHuntAction(eHuntingLodge* const b,
                eHunter* const c,
                const eAction& failAction,
                const eAction& finishAction);

    bool decide();
private:
    void findResourceDecision();
    void goBackDecision();
    void waitDecision();

    eHuntingLodge* const mLodge;
    eHunter* const mHunter;

    bool mNoResource = false;
};

#endif // EHUNTACTION_H
