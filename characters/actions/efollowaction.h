#ifndef EFOLLOWACTION_H
#define EFOLLOWACTION_H

#include <queue>

#include "ecomplexaction.h"

#include "engine/eorientation.h"

#include "pointers/estdpointer.h"

class eTile;

class eFollowAction : public eComplexAction {
public:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c,
                  const eAction& failAction,
                  const eAction& finishAction);

    void setDistance(const int d);
private:
    void increment(const int by);

    const stdptr<eCharacter> mFollow;

    struct ePathNode {
        eTile* fTile;
        eOrientation fO;
    };

    std::queue<ePathNode> mTiles;

    int mDistance = 1;
};


#endif // EFOLLOWACTION_H
