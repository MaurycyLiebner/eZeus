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
    using eCollectActionCreator = std::function<eCharacterAction*(
                                eResourceCollector* const c,
                                const eTranformFunc& tf,
                                const eAction& failAction,
                                const eAction& finishAction)>;
    eCollectResourceAction(eResourceCollector* const c,
                           const eHasResource& hr,
                           const eTranformFunc& tf,
                           const eAction& failAction,
                           const eAction& finishAction,
                           const eCollectActionCreator& cac = [](
                                eResourceCollector* const c,
                                const eTranformFunc& tf,
                                const eAction& failAction,
                                const eAction& finishAction) {
        return new eCollectAction(c, tf, failAction, finishAction);
    });

    void increment(const int by);
private:
    bool findResource();
    bool collect();
    bool goBack2();

    const eHasResource mHasResource;
    const eTranformFunc mTransFunc;
    const eCollectActionCreator mCollectCreator;
    eResourceCollector* const mCharacter;
    eResourceCollectorAction mAction{0};
};

#endif // ECOLLECTRESOURCEACTION_H
