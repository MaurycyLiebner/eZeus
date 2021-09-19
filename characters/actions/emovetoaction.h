#ifndef EMOVETOACTION_H
#define EMOVETOACTION_H

#include "ecomplexaction.h"

#include "engine/etile.h"

class eMoveToAction : public eComplexAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinal = eTileWalkable;

    eMoveToAction(eCharacter* const c,
                  const eTileWalkable& walkable,
                  const eTileFinal& final,
                  const eAction& failAction,
                  const eAction& finishAction);
    void initialize();
private:
    const eTileWalkable mWalkable;
    const eTileFinal mFinal;
};

#endif // EMOVETOACTION_H
