#ifndef EPATROLMOVEACTION_H
#define EPATROLMOVEACTION_H

#include "emoveaction.h"
#include "engine/emovedirection.h"
#include "ewalkablehelpers.h"

#include <SDL2/SDL_rect.h>

class eMovePathAction;

class eBuilding;

class eDirectionLastUseTime {
public:
    eDirectionLastUseTime() {
        for(int i = 0; i < 8; i++) {
            mTime.push_back(0);
        }
    }

    int& time(const eOrientation o) {
        const int id = static_cast<int>(o);
        return mTime[id];
    }

    void read(eReadStream& src) {
        src >> mTime;
    }

    void write(eWriteStream& dst) const {
        dst << mTime;
    }
private:
    std::vector<int> mTime;
};

using eDirectionTimes = std::map<eTile*, eDirectionLastUseTime>;

class ePatrolMoveAction : public eMoveAction {
public:
    ePatrolMoveAction(eCharacter* const c,
                      const bool diagonalOnly = true,
                      const stdsptr<eWalkableObject>& walkable =
                        eWalkableObject::sCreateRoad(),
                      const stdsptr<eDirectionTimes>& os =
                        std::make_shared<eDirectionTimes>());

    void setMaxWalkDistance(const int dist)
    { mMaxWalkDistance = dist; }
private:
    eCharacterActionState nextTurn(eOrientation& t);

    bool mDiagonalOnly;
    stdsptr<eWalkableObject> mWalkable;
    stdsptr<eDirectionTimes> mOs;

    eOrientation mO{eOrientation::topRight};
    int mMaxWalkDistance = 10000;
    int mWalkedDistance = 0;
};

#endif // EPATROLMOVEACTION_H
