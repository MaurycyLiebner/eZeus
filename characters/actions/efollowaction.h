#ifndef EFOLLOWACTION_H
#define EFOLLOWACTION_H

#include "emoveaction.h"

#include "engine/eorientation.h"

#include "pointers/estdpointer.h"

class eFollowAction : public eMoveAction {
public:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c,
                  const eAction& failAction,
                  const eAction& finishAction);
private:
    eCharacterActionState nextTurn(eOrientation& t);

    void increment(const int by);

    const stdptr<eCharacter> mFollow;

    bool mPaused = true;
    eTile* mPauseTile = nullptr;
};


#endif // EFOLLOWACTION_H
