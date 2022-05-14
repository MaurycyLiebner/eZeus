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

    void setFoundAction(const eAction& a)
    { mFoundAction = a; }

    void setFindFailAction(const eAction& a)
    { mFindFailAction = a; }

    void setWait(const bool w)
    { mWait = w; }

    void setDiagonalOnly(const bool d)
    { mDiagonalOnly = d; }

    void setMaxDistance(const int d)
    { mMaxDistance = d; }

    static bool sDefaultWalkable(eTileBase* const t);
    static bool sRoadWalkable(eTileBase* const t);
private:
    eAction mFoundAction;
    eAction mFindFailAction;
    bool mRemoveLastTurn = false;
    bool mWait = true;
    bool mDiagonalOnly = false;
    int mMaxDistance = 50;
};

#endif // EMOVETOACTION_H
