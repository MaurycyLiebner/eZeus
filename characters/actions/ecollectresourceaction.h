#ifndef ECOLLECTRESOURCEACTION_H
#define ECOLLECTRESOURCEACTION_H

#include <vector>

#include "emovepathaction.h"
#include "engine/emovedirection.h"

class eMovePathAction;
enum class eResourceCollectorAction : int;

class eResourceCollector;

class eCollectResourceAction : public eCharacterAction {
public:
    using eHasResource = std::function<bool(eTile*)>;
    using eTranformFunc = std::function<void(eTile*)>;
    eCollectResourceAction(eResourceCollector* const c,
                           const eHasResource& hr,
                           const eTranformFunc& tf,
                           const eAction& failAction,
                           const eAction& finishAction);

    void increment(const int by);
private:
    bool findResource();
    bool collect();
    bool goBack();

    const eHasResource mHasResource;
    const eTranformFunc mTransFunc;
    eResourceCollector* const mCharacter;

    int mStartX{0};
    int mStartY{0};
    eResourceCollectorAction mAction{0};
    eCharacterAction* mCurrentAction = nullptr;
};

#endif // ECOLLECTRESOURCEACTION_H
