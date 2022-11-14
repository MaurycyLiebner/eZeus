#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "buildings/eresourcecollectbuilding.h"
#include "emovetoaction.h"
#include "engine/egameboard.h"

eCollectResourceAction::eCollectResourceAction(
        eResourceCollectBuildingBase* const b,
        eCharacter* const c,
        const stdsptr<eHasResourceObject>& hr) :
    eActionWithComeback(c, eCharActionType::collectResourceAction),
    mHasResource(hr),
    mBuilding(b) {}

eCollectResourceAction::eCollectResourceAction(eCharacter* const c) :
    eCollectResourceAction(nullptr, c, nullptr) {}

bool eCollectResourceAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    if(mDisabled) {
        goBackDecision();
        return true;
    }

    const auto c = character();
    const auto cc = static_cast<eResourceCollectorBase*>(c);

    const auto t = c->tile();
    const int coll = cc->collected();

    const bool inside = eWalkableHelpers::sTileUnderBuilding(t, mBuilding) ||
                        t == startTile();

    if(coll > 0) {
        if(inside) {
            if(mAddResource) mBuilding->addRaw();
            cc->incCollected(-coll);
            if(mFinishOnce) {
                setState(eCharacterActionState::finished);
                return true;
            } else {
                waitDecision();
            }
        } else {
            goBackDecision();
        }
    } else {
        const auto& brd = c->getBoard();
        eTile* tt = nullptr;
        if(mGetAtTile) {
            const auto t = c->tile();
            if(mHasResource->has(t) && !t->busy()) {
                tt = t;
            }
        } else {
            for(int i = -1; i < 2; i++) {
                for(int j = -1; j < 2; j++) {
                    const auto ttt = brd.tile(t->x() + i, t->y() + j);
                    if(!ttt) continue;
                    if(mHasResource->has(ttt) && !ttt->busy()) {
                        tt = ttt;
                        break;
                    }
                }
            }
        }
        if(tt) collect(tt);
        else if(inside) {
            const int res = mBuilding->resource();
            if(res >= mBuilding->maxResource() ||
               !mBuilding->enabled()) {
                waitDecision();
            } else {
                if(mNoTarget) {
                    mNoTarget = false;
                    waitDecision();
                } else {
                    findResourceDecision();
                }
            }
        } else if(mNoTarget) {
            mNoTarget = false;
            goBackDecision();
        } else {
            findResourceDecision();
        }
    }

    return true;
}

void eCollectResourceAction::setCollectedAction(const eTileActionType a) {
    mCollectedAction = a;
}

void eCollectResourceAction::callCollectedAction(eTile* const tile) const {
    switch(mCollectedAction) {
    case eTileActionType::none:
        break;
    case eTileActionType::masonry: {
        const auto r = e::make_shared<eCartTransporter>(board());
        r->changeTile(tile);
        r->setBigTrailer(true);
        r->setResource(eResourceType::marble, 1);

        const auto finish = std::make_shared<eCRA_callCollectedActionFinish>(
                                board(), mBuilding);
        const auto a = e::make_shared<eMoveToAction>(r.get());
        a->setFinishAction(finish);
        a->start(mBuilding);
        r->setAction(a);
        r->setActionType(eCharacterActionType::walk);
    } break;
    }
}

void eCollectResourceAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    mHasResource = src.readHasResource();
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mBuilding = static_cast<eResourceCollectBuildingBase*>(b);
    });
    src >> mCollectedAction;
    mWalkable = src.readWalkable();
    src >> mDisabled;
    src >> mWaitTime;
    src >> mFinishOnce;
    src >> mAddResource;
    src >> mGetAtTile;
    src >> mNoTarget;
}

void eCollectResourceAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst.writeHasResource(mHasResource.get());
    dst.writeBuilding(mBuilding);
    dst << mCollectedAction;
    dst.writeWalkable(mWalkable.get());
    dst << mDisabled;
    dst << mWaitTime;
    dst << mFinishOnce;
    dst << mAddResource;
    dst << mGetAtTile;
    dst << mNoTarget;
}

bool eCollectResourceAction::findResourceDecision() {
    const auto c = character();

    const stdptr<eCollectResourceAction> tptr(this);

    const auto tileWalkable = eWalkableObject::sCreateHasResource(
                                  mHasResource, mWalkable);

    const auto hr = mHasResource;
    const auto hubr = [hr](eTileBase* const t) {
        return !t->busy() && hr->has(t);
    };

    const auto a = e::make_shared<eMoveToAction>(c);

    const stdptr<eCharacter> cptr(c);
    a->setFoundAction([cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });

    const auto findFailFunc = [tptr, this]() {
        if(tptr) mNoTarget = true;
    };
    a->setFindFailAction(findFailFunc);
    a->setRemoveLastTurn(!mGetAtTile);

    a->start(hubr, tileWalkable);
    setCurrentAction(a);

    return false;
}

bool eCollectResourceAction::collect(eTile* const tile) {
    tile->setBusy(true);
    const auto c = character();
    c->setActionType(eCharacterActionType::collect);

    const auto failAction = std::make_shared<eCRA_collectFail>(
                                board(), tile);
    const auto finishAction = std::make_shared<eCRA_collectFinish>(
                                  board(), this, tile);

    const auto a = e::make_shared<eCollectAction>(c);
    a->setFailAction(failAction);
    a->setFinishAction(finishAction);
    a->setDeleteFailAction(failAction);
    setCurrentAction(a);
    return false;
}

void eCollectResourceAction::goBackDecision() {
    const auto c = character();
    const auto cc = static_cast<eResourceCollectorBase*>(c);

    if(cc->collected()) {
        c->setActionType(eCharacterActionType::carry);
    } else {
        c->setActionType(eCharacterActionType::walk);
    }
    const auto tileWalkable = eWalkableObject::sCreateHasResource(
                                  mHasResource, mWalkable);
    goBack(mBuilding, tileWalkable);
}

void eCollectResourceAction::waitDecision() {
    wait(mWaitTime);
}

