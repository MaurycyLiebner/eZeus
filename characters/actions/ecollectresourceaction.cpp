#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

eCollectResourceAction::eCollectResourceAction(
        eResourceCollector* const c,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const eAction& failAction,
        const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mHasResource(hr),
    mTransFunc(tf),
    mCharacter(c) {
    const auto t = c->tile();
    if(t) {
        mStartX = t->x();
        mStartY = t->y();
    }
}

void eCollectResourceAction::increment(const int by) {
    if(mCurrentAction) mCurrentAction->increment(by);
    else findResource();
}

bool eCollectResourceAction::findResource() {
    mAction = eResourceCollectorAction::walk;
    mCharacter->setAction(mAction);
    const auto c = character();
    const auto t = c->tile();

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        collect();
    };

    const auto tileWalkable0 = [](eTile* const t) {
        (void)t;
        return true;
    };
    const auto pf0 = ePathFinder(t, tileWalkable0, mHasResource);
    std::vector<eOrientation> path0;
    const bool r0 = pf0.findPath(100, path0, false, false);
    if(r0) {
        mCurrentAction = new eMovePathAction(c, path0, tileWalkable0,
                                             failAction, finishAction);
        return true;
    }
    setState(eCharacterActionState::failed);
    return false;
}

class eCollectAction : public eCharacterAction {
public:
    using eTranformFunc = std::function<void(eTile*)>;
    eCollectAction(
            eTile* const tile,
            eResourceCollector* const c,
            const eTranformFunc& tf,
            const eAction& failAction,
            const eAction& finishAction) :
        eCharacterAction(c, failAction, finishAction),
        mCharacter(c), mTile(tile),
        mTransFunc(tf) {}


    void increment(const int by) {
        mTime += by;
        if(mTime > 100) {
            mTile->decResource(by);
            mCharacter->incCollected(by);
            const bool noResLeft = mTile->resource() <= 0;
            if(noResLeft) mTransFunc(mTile);
            if(noResLeft || mCharacter->collected() >= 100) {
                setState(eCharacterActionState::finished);
            }
            mTime = 0;
        }
    }
private:
    int mTime = 0;
    eResourceCollector* const mCharacter;
    eTile* const mTile;
    const eTranformFunc mTransFunc;
};

bool eCollectResourceAction::collect() {
    mAction = eResourceCollectorAction::collect;
    mCharacter->setAction(mAction);
    const auto c = character();
    const auto t = c->tile();

    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        goBack();
    };

    mCurrentAction = new eCollectAction(t, mCharacter,
                                        mTransFunc,
                                        failAction,
                                        finishAction);
    return false;
}

bool eCollectResourceAction::goBack() {
    mAction = eResourceCollectorAction::carry;
    mCharacter->setAction(mAction);
    const auto c = character();
    const auto t = c->tile();

    const auto finalTile = [this](eTile* const t) {
        return t->x() == mStartX && t->y() == mStartY;
    };
    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        setState(eCharacterActionState::finished);
    };

    const auto tileWalkable0 = [](eTile* const t) {
        (void)t;
        return true;
    };
    const auto pf0 = ePathFinder(t, tileWalkable0, finalTile);
    std::vector<eOrientation> path0;
    const bool r0 = pf0.findPath(100, path0, false, false);
    if(r0) {
        mCurrentAction = new eMovePathAction(c, path0, tileWalkable0,
                                             failAction, finishAction);
        return true;
    }
    setState(eCharacterActionState::failed);
    return false;
}
