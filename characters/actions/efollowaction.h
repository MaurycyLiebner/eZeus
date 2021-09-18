#ifndef EFOLLOWACTION_H
#define EFOLLOWACTION_H

#include "emoveaction.h"

#include "engine/eorientation.h"

#include "pointers/estdpointer.h"

class eFollowAction : public eCharacterAction {
public:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c,
                  const eAction& failAction,
                  const eAction& finishAction);

    void setDistance(const int d);
private:
    void increment(const int by);

    const stdptr<eCharacter> mFollow;

    int mDistance = 1;
    bool mPaused = true;
    eTile* mPauseTile = nullptr;
};


#endif // EFOLLOWACTION_H
