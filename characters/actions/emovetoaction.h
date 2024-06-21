#ifndef EMOVETOACTION_H
#define EMOVETOACTION_H

#include "ecomplexaction.h"

#include "engine/etile.h"
#include "engine/thread/ethreadtile.h"
#include "ewalkablehelpers.h"

class eThreadBoard;

using eAction = std::function<void()>;
using eTileGetter = std::function<eThreadTile*(eThreadBoard&)>;

class eMoveToAction : public eComplexAction {
public:
    eMoveToAction(eCharacter* const c);

    bool decide() { return false; }

    using eTileFinal = std::function<bool(eThreadTile* const)>;
    void start(const eTileFinal& final,
               stdsptr<eWalkableObject> pathFindWalkable =
                   eWalkableObject::sCreateDefault(),
               stdsptr<eWalkableObject> moveWalkable = nullptr,
               const eTileGetter& endTile = nullptr);
    void start(eTile* const final,
               const stdsptr<eWalkableObject>& pathFindWalkable =
                    eWalkableObject::sCreateDefault(),
               const stdsptr<eWalkableObject>& moveWalkable = nullptr,
               const eTileGetter& endTile = nullptr);
    void start(const SDL_Rect& rect,
               stdsptr<eWalkableObject> pathFindWalkable =
                    eWalkableObject::sCreateDefault(),
               stdsptr<eWalkableObject> moveWalkable = nullptr,
               const eTileGetter& endTile = nullptr);
    void start(eBuilding* const final,
               const stdsptr<eWalkableObject>& pathFindWalkable =
                    eWalkableObject::sCreateDefault(),
               const stdsptr<eWalkableObject>& moveWalkable = nullptr,
               const eTileGetter& endTile = nullptr);
    void start(const eBuildingType final,
               const stdsptr<eWalkableObject>& pathFindWalkable =
                    eWalkableObject::sCreateDefault(),
               const stdsptr<eWalkableObject>& moveWalkable = nullptr,
               const eTileGetter& endTile = nullptr);

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

    void setMaxFindDistance(const int d)
    { mMaxFindDistance = d; }

    void setMaxWalkDistance(const int d)
    { mMaxWalkDistance = d; };

    void setObsticleHandler(const stdsptr<eObsticleHandler>& oh);

    int pathLength() const
    { return mPathLength; }

    using eTileDistance = std::function<int(eTileBase* const)>;
    void setTileDistance(const eTileDistance& dist);
private:
    eAction mFoundAction;
    eAction mFindFailAction;
    bool mRemoveLastTurn = false;
    bool mWait = true;
    bool mDiagonalOnly = false;
    int mMaxFindDistance = 10000;
    int mMaxWalkDistance = 10000;
    int mPathLength = 0;
    stdsptr<eObsticleHandler> mObstHandler;
    eTileDistance mDistance;
};

#endif // EMOVETOACTION_H
