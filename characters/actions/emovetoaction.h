#ifndef EMOVETOACTION_H
#define EMOVETOACTION_H

#include "ecomplexaction.h"

#include "engine/etile.h"

class eMoveToAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinal = eTileWalkable;
    void initialize(const eTileWalkable& walkable,
                    const eTileFinal& final);
};

#endif // EMOVETOACTION_H
