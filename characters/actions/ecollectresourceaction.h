#ifndef ECOLLECTRESOURCEACTION_H
#define ECOLLECTRESOURCEACTION_H

#include "eactionwithcomeback.h"

#include "emovepathaction.h"
#include "engine/emovedirection.h"
#include "ecollectaction.h"

class eMovePathAction;

class eResourceCollectorBase;
class eResourceCollectBuilding;

class eCollectResourceAction : public eActionWithComeback {
public:
    using eHasResource = std::function<bool(eTileBase*)>;
    using eTileAction = std::function<void(eTile*)>;
    using eTranformFunc = eTileAction;
    eCollectResourceAction(eResourceCollectBuilding* const b,
                           eResourceCollectorBase* const c,
                           const eHasResource& hr,
                           const eTranformFunc& tf,
                           const eAction& failAction,
                           const eAction& finishAction);

    bool decide();

    void setCollectedAction(const eTileAction& a);

    void setGetAtTile(const bool b) { mGetAtTile = b; }
    void setAddResource(const bool b) { mAddResource = b; }
private:
    bool findResourceDecision();
    bool collect(eTile* const tile);
    void goBackDecision();
    void waitDecision();

    const eHasResource mHasResource;
    const eTranformFunc mTransFunc;
    eResourceCollectBuilding* const mBuilding;
    eResourceCollectorBase* const mCharacter;
    eTileAction mCollectedAction;

    bool mFinishOnce = true;

    bool mAddResource = true;

    bool mGetAtTile = true;

    bool mNoTarget = false;
};

#endif // ECOLLECTRESOURCEACTION_H
