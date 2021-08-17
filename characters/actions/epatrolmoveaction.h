#ifndef EPATROLMOVEACTION_H
#define EPATROLMOVEACTION_H

#include "emoveaction.h"
#include "engine/emovedirection.h"

class eMovePathAction;

struct ePatrolGuide {
    int fX;
    int fY;
    eMoveDirection fDir;
};

class ePatrolMoveAction : public eMoveAction {
public:
    ePatrolMoveAction(eCharacter* const c,
                      const std::vector<ePatrolGuide>& guides,
                      const eAction& failAction,
                      const eAction& finishAction);
private:
    bool getGuide(const int tx, const int ty,
                  ePatrolGuide& result);

    eCharacterActionState nextTurn(eOrientation& t);

    eOrientation mO{eOrientation::topRight};
    int mMaxDistance = 100;
    int mWalkedDistance = 0;
    int mStartX = 0;
    int mStartY = 0;
    std::vector<ePatrolGuide> mGuides;
};

#endif // EPATROLMOVEACTION_H
