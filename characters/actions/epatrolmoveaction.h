#ifndef EPATROLMOVEACTION_H
#define EPATROLMOVEACTION_H

#include "emoveaction.h"
#include "engine/emovedirection.h"

#include <SDL2/SDL_rect.h>

class eMovePathAction;

class eBuilding;

class ePatrolMoveAction : public eMoveAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    ePatrolMoveAction(eCharacter* const c,
                      const eAction& failAction,
                      const eAction& finishAction,
                      const bool diagonalOnly = true,
                      const eTileWalkable& walkable = sRoadWalkable);

    static bool sRoadWalkable(eTileBase* const tile);

    void setMaxDistance(const int dist);
private:
    eCharacterActionState nextTurn(eOrientation& t);

    const bool mDiagonalOnly;
    const eTileWalkable mWalkable;

    eOrientation mO{eOrientation::topRight};
    int mMaxDistance = 100;
    int mWalkedDistance = 0;
};

#endif // EPATROLMOVEACTION_H
