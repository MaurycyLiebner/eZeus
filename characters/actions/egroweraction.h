#ifndef EGROWERACTION_H
#define EGROWERACTION_H

#include "eactionwithcomeback.h"

#include "characters/egrower.h"
#include "buildings/egrowerslodge.h"

class eGrowerAction : public eActionWithComeback {
public:
    eGrowerAction(const eGrowerType type,
                  eGrowersLodge* const lodge,
                  eGrower* const c,
                  const eAction& failAction,
                  const eAction& finishAction);

    bool decide();
private:
    bool findResourceDecision();
    void workOnDecision(eTile* const tile);
    void goBackDecision();
    void waitDecision();

    const eGrowerType mType;
    eGrower* const mGrower;
    eGrowersLodge* const mLodge;

    bool mFinishOnce = true;

    int mGroomed = 0;
    bool mNoResource = false;
};

#endif // EGROWERACTION_H
