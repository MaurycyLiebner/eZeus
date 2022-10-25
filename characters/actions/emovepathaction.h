#ifndef EMOVEPATHACTION_H
#define EMOVEPATHACTION_H

#include "emoveaction.h"

class eMovePathAction : public eMoveAction {
public:
    eMovePathAction(eCharacter* const c,
                    const std::vector<eOrientation>& path,
                    const eTileWalkable& tileWalkable,
                    const eAction& failAction,
                    const eAction& finishAction);

    void setMaxDistance(const int dist) { mMaxDistance = dist; }
private:
    eCharacterActionState nextTurn(eOrientation& turn);

    std::vector<eOrientation> mTurns;

    int mMaxDistance = 1000;
    int mWalkedDistance = 0;
};


#endif // EMOVEPATHACTION_H
