#ifndef EMOVETOACTION_H
#define EMOVETOACTION_H

#include "ecomplexaction.h"

#include "engine/etile.h"
#include "engine/thread/ethreadtile.h"

class eMoveToAction : public eComplexAction {
public:
    using eComplexAction::eComplexAction;

    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinal = std::function<bool(eThreadTile* const)>;
    void start(const eTileFinal& final,
               eTileWalkable walkable =
                   sDefaultWalkable);
    void start(eTile* const final,
               const eTileWalkable& walkable =
                   sDefaultWalkable);
    void start(eBuilding* const final,
               const eTileWalkable& walkable =
                   sDefaultWalkable);
    void start(const eBuildingType final,
               const eTileWalkable& walkable =
                   sDefaultWalkable);

    void setRemoveLastTurn(const bool r)
    { mRemoveLastTurn = r; }

    static bool sDefaultWalkable(eTileBase* const t);
    static bool sRoadWalkable(eTileBase* const t);
private:
    bool mRemoveLastTurn = false;
};

#endif // EMOVETOACTION_H
