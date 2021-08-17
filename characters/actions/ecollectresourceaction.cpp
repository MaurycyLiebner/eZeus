﻿#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"
#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"

eCollectResourceAction::eCollectResourceAction(
        eResourceCollector* const c,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mTransFunc(tf),
    mCharacter(c) {
}

void eCollectResourceAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eCollectResourceAction::resume() {
    mCharacter->setActionType(mAction);
}

bool eCollectResourceAction::findResource() {
    mAction = eCharacterActionType::walk;
    mCharacter->setActionType(mAction);
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };

    const auto hr = mHasResource;

    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto tileWalkable = [hr](eTileBase* const t) {
        return t->walkable() || hr(t);
    };
    const auto hubr = [hr](eTileBase* const t) {
        return hr(t) && !t->busy();
    };
    const auto finishFunc = [this, c, tileWalkable, failFunc](
                            const std::vector<eOrientation>& path) {
        const auto finishAction = [this, c]() {
            const auto tile = c->tile();
            if(mHasResource(tile) && !tile->busy()) collect(tile);
            else findResource();
        };

        const auto a  = new eMovePathAction(c, path, tileWalkable,
                                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       hubr, finishFunc,
                                       failFunc);
    tp->queueTask(pft);

    setCurrentAction(new eWaitAction(c, []() {}, []() {}));
    return false;
}

bool eCollectResourceAction::collect(eTile* const tile) {
    tile->setBusy(true);
    mAction = eCharacterActionType::collect;
    mCharacter->setActionType(mAction);

    const auto failAction = [this, tile]() {
        tile->setBusy(false);
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this, tile]() {
        tile->setBusy(false);
        goBack2();
    };

    const auto a = new eCollectAction(mCharacter, mTransFunc,
                                      failAction, finishAction);
    setCurrentAction(a);
    return false;
}

bool eCollectResourceAction::goBack2() {
    mAction = eCharacterActionType::carry;
    mCharacter->setActionType(mAction);
    return eActionWithComeback::goBack([this](eTileBase* const t) {
        return t->walkable() || mHasResource(t);
    });
}
