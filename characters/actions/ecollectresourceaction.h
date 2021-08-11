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
    using eHasResource = std::function<bool(eTile*)>;
    using eTranformFunc = std::function<void(eTile*)>;
    eCollectResourceAction(eResourceCollector* const c,
                           const eHasResource& hr,
                           const eTranformFunc& tf,
                           const eAction& failAction,
                           const eAction& finishAction);

    void increment(const int by);

    void resume();
private:
    bool findResource();
    bool collect();
    bool goBack2();

    const eHasResource mHasResource;
    const eTranformFunc mTransFunc;
    eResourceCollector* const mCharacter;
    eResourceCollectorAction mAction{0};
};

#endif // ECOLLECTRESOURCEACTION_H
