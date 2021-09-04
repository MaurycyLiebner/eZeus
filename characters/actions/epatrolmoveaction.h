#ifndef EPATROLMOVEACTION_H
#define EPATROLMOVEACTION_H

#include "emoveaction.h"
#include "engine/emovedirection.h"

class eMovePathAction;
struct SDL_Rect;

class ePatrolMoveAction : public eMoveAction {
public:
    ePatrolMoveAction(eCharacter* const c,
                      const SDL_Rect& buildingRect,
                      const eAction& failAction,
                      const eAction& finishAction);
private:
    eCharacterActionState nextTurn(eOrientation& t);

    eOrientation mO{eOrientation::topRight};
    int mMaxDistance = 100;
    int mWalkedDistance = 0;
};

#endif // EPATROLMOVEACTION_H
