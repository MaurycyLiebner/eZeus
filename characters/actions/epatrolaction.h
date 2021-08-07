#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include <vector>

#include "emoveaction.h"
#include "engine/emovedirection.h"

class eMovePathAction;


struct ePatrolGuide {
    int fX;
    int fY;
    eMoveDirection fDir;
};

class ePatrolAction : public eMoveAction {
public:
    ePatrolAction(eCharacter* const c,
                  const std::vector<ePatrolGuide>& guides,
                  const eAction& failAction,
                  const eAction& finishAction);

    void increment(const int by);
private:
    bool getGuide(const int tx, const int ty,
                  ePatrolGuide& result);
    bool goBack();

    eCharacterActionState nextTurn(eOrientation& t);

    eOrientation mO{eOrientation::topRight};
    int mMaxDistance = 20;
    int mWalkedDistance = 0;
    int mStartX = 0;
    int mStartY = 0;
    bool mGoBack = false;
    eMovePathAction* mGoBackAction = nullptr;
    std::vector<ePatrolGuide> mGuides;
};

#endif // EPATROLACTION_H
