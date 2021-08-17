#ifndef ECOLLECTRESOURCEACTION_H
#define ECOLLECTRESOURCEACTION_H

#include "eactionwithcomeback.h"

#include "emovepathaction.h"
#include "engine/emovedirection.h"
#include "ecollectaction.h"

class eMovePathAction;
enum class eResourceCollectorAction : int;

class eResourceCollector;

class eCollectResourceAction : public eActionWithComeback {
public:
    using eHasResource = std::function<bool(eTileBase*)>;
    using eTranformFunc = std::function<void(eTile*)>;
    eCollectResourceAction(eResourceCollector* const c,
                           const eHasResource& hr,
                           const eTranformFunc& tf,
                           const eAction& failAction,
                           const eAction& finishAction);

    void increment(const int by);
private:
    bool findResource();
    bool collect(eTile* const tile);
    bool goBack2();

    const eHasResource mHasResource;
    const eTranformFunc mTransFunc;
    eResourceCollector* const mCharacter;
};

#endif // ECOLLECTRESOURCEACTION_H
