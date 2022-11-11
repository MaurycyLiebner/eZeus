#ifndef EPATROLMOVEACTION_H
#define EPATROLMOVEACTION_H

#include "emoveaction.h"
#include "engine/emovedirection.h"
#include "ewalkablehelpers.h"

#include <SDL2/SDL_rect.h>

class eMovePathAction;

class eBuilding;

class eDirectionUsage {
public:
    eDirectionUsage() {
        for(int i = 0; i < 8; i++) {
            mUsage.push_back(0);
        }
    }

    int& usage(const eOrientation o) {
        const int id = static_cast<int>(o);
        return mUsage[id];
    }
private:
    std::vector<int> mUsage;
};

class ePatrolMoveAction : public eMoveAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    ePatrolMoveAction(eCharacter* const c,
                      const eAction& failAction,
                      const eAction& finishAction,
                      const bool diagonalOnly = true,
                      const eTileWalkable& walkable =
                        eWalkableHelpers::sRoadWalkable);

    void setMaxWalkDistance(const int dist)
    { mMaxWalkDistance = dist; }
private:
    eCharacterActionState nextTurn(eOrientation& t);

    const bool mDiagonalOnly;
    const eTileWalkable mWalkable;

    eOrientation mO{eOrientation::topRight};
    int mMaxWalkDistance = 10000;
    int mWalkedDistance = 0;

    std::map<eTile*, eDirectionUsage> mOs;
};

#endif // EPATROLMOVEACTION_H
