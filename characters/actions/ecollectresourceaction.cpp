#include "ecollectresourceaction.h"

#include "characters/eresourcecollector.h"
#include "buildings/eresourcecollectbuilding.h"
#include "emovetoaction.h"
#include "engine/egameboard.h"

eCollectResourceAction::eCollectResourceAction(
        eResourceCollectBuilding* const b,
        eResourceCollectorBase* const c,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mHasResource(hr),
    mTransFunc(tf),
    mBuilding(b),
    mCharacter(c) {}

bool eCollectResourceAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    const auto t = mCharacter->tile();
    const int coll = mCharacter->collected();

    const bool inside = eWalkableHelpers::sTileUnderBuilding(t, mBuilding);

    if(coll > 0) {
        if(inside) {
            const auto rType = mBuilding->resourceType();
            if(mAddResource) mBuilding->add(rType, coll);
            mCharacter->incCollected(-coll);
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
        const auto& brd = mCharacter->getBoard();
        eTile* tt = nullptr;
        if(mGetAtTile) {
            const auto t = mCharacter->tile();
            if(mHasResource(t) && !t->busy()) {
                tt = t;
            }
        } else {
            for(int i = -1; i < 2; i++) {
                for(int j = -1; j < 2; j++) {
                    const auto ttt = brd.tile(t->x() + i, t->y() + j);
                    if(!ttt) continue;
                    if(mHasResource(ttt) && !ttt->busy()) {
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

void eCollectResourceAction::setCollectedAction(const eTileAction& a) {
    mCollectedAction = a;
}

bool eCollectResourceAction::findResourceDecision() {
    const auto c = character();

    const stdptr<eCollectResourceAction> tptr(this);

    const auto hr = mHasResource;
    const auto tileWalkable = [hr](eTileBase* const t) {
        return t->walkable() || hr(t);
    };

    const auto hubr = [hr](eTileBase* const t) {
        return hr(t) && !t->busy();
    };

    const auto a = e::make_shared<eMoveToAction>(c, [](){}, [](){});

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
    mCharacter->setActionType(eCharacterActionType::collect);

    const auto failAction = [tile]() {
        tile->setBusy(false);
    };
    const eStdPointer<eCollectResourceAction> tptr(this);

    const auto finishAction = [tptr, this, tile]() {
        tile->setBusy(false);
        if(!tptr) return;
        if(mCollectedAction) mCollectedAction(tile);
    };

    const auto a = e::make_shared<eCollectAction>(
                       mCharacter, mTransFunc,
                       failAction, finishAction);
    setCurrentAction(a);
    return false;
}

void eCollectResourceAction::goBackDecision() {
    if(mCharacter->collected()) {
        mCharacter->setActionType(eCharacterActionType::carry);
    } else {
        mCharacter->setActionType(eCharacterActionType::walk);
    }
    const auto hr = mHasResource;
    goBack(mBuilding, [hr](eTileBase* const t) {
        return eWalkableHelpers::sDefaultWalkable(t) || hr(t);
    });
}

void eCollectResourceAction::waitDecision() {
    wait(5000);
}

