#ifndef EPATROLACTION_H
#define EPATROLACTION_H

#include <vector>

#include "emoveaction.h"

class eMovePathAction;

enum class eMoveDirection {
    topRight = 1 << 0,
    bottomRight = 1 << 1,
    bottomLeft = 1 << 2,
    topLeft = 1 << 3
};

inline eMoveDirection operator|(const eMoveDirection a, const eMoveDirection b) {
    return static_cast<eMoveDirection>(static_cast<int>(a) | static_cast<int>(b));
}

inline eMoveDirection operator&(const eMoveDirection a, const eMoveDirection b) {
    return static_cast<eMoveDirection>(static_cast<int>(a) & static_cast<int>(b));
}

inline std::vector<eMoveDirection> gExtractDirections(
        const eMoveDirection d) {
    std::vector<eMoveDirection> dirs;
    if(static_cast<bool>(d & eMoveDirection::topRight)) {
        dirs.push_back(eMoveDirection::topRight);
    }
    if(static_cast<bool>(d & eMoveDirection::bottomRight)) {
        dirs.push_back(eMoveDirection::bottomRight);
    }
    if(static_cast<bool>(d & eMoveDirection::bottomLeft)) {
        dirs.push_back(eMoveDirection::bottomLeft);
    }
    if(static_cast<bool>(d & eMoveDirection::topLeft)) {
        dirs.push_back(eMoveDirection::topLeft);
    }
    return dirs;
}

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
