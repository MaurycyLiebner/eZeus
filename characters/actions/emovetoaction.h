#ifndef EMOVETOACTION_H
#define EMOVETOACTION_H

#include "ecomplexaction.h"

#include "engine/etile.h"

class eMoveToAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinal = eTileWalkable;
    void start(const eTileFinal& final,
               const eTileWalkable& walkable =
                   sDefaultWalkable);
    void start(eTile* const final,
               const eTileWalkable& walkable =
                   sDefaultWalkable);
    void start(eBuilding* const final,
               const eTileWalkable& walkable =
                   sDefaultWalkable);

    static bool sDefaultWalkable(eTileBase* const t);
};

#endif // EMOVETOACTION_H
