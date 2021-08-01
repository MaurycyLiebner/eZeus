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
private:
    eCharacterActionState nextTurn(eOrientation& turn);

    std::vector<eOrientation> mTurns;
};


#endif // EMOVEPATHACTION_H
