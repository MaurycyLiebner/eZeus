#ifndef ECOLLECTRESOURCEACTION_H
#define ECOLLECTRESOURCEACTION_H

#include "eactionwithcomeback.h"

#include "emovepathaction.h"
#include "engine/emovedirection.h"
#include "ecollectaction.h"
#include "ewalkablehelpers.h"

class eMovePathAction;

class eResourceCollectorBase;
class eResourceCollectBuildingBase;

class eCollectResourceAction : public eActionWithComeback {
public:
    using eHasResource = std::function<bool(eTileBase*)>;
    using eTileAction = std::function<void(eTile*)>;
    using eTranformFunc = std::function<void(eTile*, eGameBoard& board)>;
    eCollectResourceAction(eResourceCollectBuildingBase* const b,
                           eResourceCollectorBase* const c,
                           const eHasResource& hr,
                           const eTranformFunc& tf,
                           const eAction& failAction,
                           const eAction& finishAction);

    bool decide();

    void setCollectedAction(const eTileAction& a);

    void setGetAtTile(const bool b) { mGetAtTile = b; }
    void setAddResource(const bool b) { mAddResource = b; }
    void setWalkable(const eWalkable& w) { mWalkable = w; }

    void setFinishOnce(const bool f) { mFinishOnce = f; }
    void setWaitTime(const int w) { mWaitTime = w; }

    void setDisabled(const bool d) { mDisabled = d; }
private:
    bool findResourceDecision();
    bool collect(eTile* const tile);
    void goBackDecision();
    void waitDecision();

    const eHasResource mHasResource;
    const eTranformFunc mTransFunc;
    eResourceCollectBuildingBase* const mBuilding;
    eResourceCollectorBase* const mCharacter;
    eTileAction mCollectedAction;
    eWalkable mWalkable = eWalkableHelpers::sDefaultWalkable;

    bool mDisabled = false;
    int mWaitTime = 5000;

    bool mFinishOnce = true;

    bool mAddResource = true;

    bool mGetAtTile = true;

    bool mNoTarget = false;
};

#endif // ECOLLECTRESOURCEACTION_H
