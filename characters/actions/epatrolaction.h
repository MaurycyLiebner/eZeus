#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include <vector>

#include "emoveaction.h"

class eMovePathAction;

enum class eMoveDirection {
    topRight,
    bottomRight,
    bottomLeft,
    topLeft
};

struct ePatrolGuide {
    int fX;
    int fY;
    eMoveDirection fDir;
};

class ePatrolAction : public eMoveAction {
public:
    ePatrolAction(eCharacter* const c,
                  const eAction& failAction,
                  const eAction& finishAction);

    void increment();
private:
    bool getGuide(const int tx, const int ty,
                  ePatrolGuide& result);
    bool goBack();

    eCharacterActionState nextTurn(eOrientation& t);

    eOrientation mO{eOrientation::topRight};
    int mMaxDistance = 50;
    int mWalkedDistance = 0;
    int mStartX;
    int mStartY;
    eMovePathAction* mGoBackAction = nullptr;
    std::vector<ePatrolGuide> mGuides;
};

#endif // EPATROLACTION_H
