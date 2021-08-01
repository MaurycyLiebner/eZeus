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

inline eOrientation directionToOrientation(const eMoveDirection dir) {
    switch(dir) {
    case eMoveDirection::topRight:
        return eOrientation::topRight;
    case eMoveDirection::bottomRight:
        return eOrientation::bottomRight;
    case eMoveDirection::bottomLeft:
        return eOrientation::bottomLeft;
    case eMoveDirection::topLeft:
        return eOrientation::topLeft;
    }
    return eOrientation::topRight;
}


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
