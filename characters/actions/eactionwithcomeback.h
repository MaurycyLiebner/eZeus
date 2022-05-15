#ifndef EACTIONWITHCOMEBACK_H
#define EACTIONWITHCOMEBACK_H

#include "ecomplexaction.h"
#include "emovepathaction.h"
#include "engine/emovedirection.h"

class eBuilding;

class eActionWithComeback : public eComplexAction {
public:
    eActionWithComeback(eCharacter* const c,
                        const eAction& failAction,
                        const eAction& finishAction);

    bool decide();
protected:
    using eWalkable = std::function<bool(eTileBase*)>;
    void goBack(const eWalkable& walkable);
    void goBack(eBuilding* const b,
                const eWalkable& walkable);
private:
    void teleportDecision();

    eTile* const mStartTile;

    bool mGoBackFail = false;
};

#endif // EACTIONWITHCOMEBACK_H
