#ifndef ECOLLECTRESOURCEACTION_H
#define ECOLLECTRESOURCEACTION_H

#include "eactionwithcomeback.h"

#include "emovepathaction.h"
#include "engine/emovedirection.h"
#include "ecollectaction.h"
#include "ewalkablehelpers.h"
#include "walkable/ehasresourceobject.h"
#include "buildings/eresourcecollectbuildingbase.h"

class eMovePathAction;

class eResourceCollectorBase;
class eResourceCollectBuildingBase;

enum class eTileActionType {
    none,
    masonry
};

class eCollectResourceAction : public eActionWithComeback {
public:
    eCollectResourceAction(eResourceCollectBuildingBase* const b,
                           eCharacter* const c,
                           const stdsptr<eHasResourceObject>& hr);
    eCollectResourceAction(eCharacter* const c);

    bool decide() override;

    void setCollectedAction(const eTileActionType a);
    void callCollectedAction(eTile* const tile) const;

    void setGetAtTile(const bool b) { mGetAtTile = b; }
    void setAddResource(const bool b) { mAddResource = b; }
    void setWalkable(const stdsptr<eWalkableObject> & w) { mWalkable = w; }

    void setFinishOnce(const bool f) { mFinishOnce = f; }
    void setWaitTime(const int w) { mWaitTime = w; }

    void setDisabled(const bool d) { mDisabled = d; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool findResourceDecision();
    bool collect(eTile* const tile);
    void goBackDecision();
    void waitDecision();

    stdsptr<eHasResourceObject> mHasResource;
    eResourceCollectBuildingBase* mBuilding = nullptr;
    eTileActionType mCollectedAction = eTileActionType::none;
    stdsptr<eWalkableObject> mWalkable =
            eWalkableObject::sCreateDefault();

    bool mDisabled = false;
    int mWaitTime = 5000;

    bool mFinishOnce = true;

    bool mAddResource = true;

    bool mGetAtTile = true;

    bool mNoTarget = false;
};

class eCRA_collectFinish : public eCharActFunc {
public:
    eCRA_collectFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::CRA_collectFinish) {}
    eCRA_collectFinish(eGameBoard& board,
                       eCollectResourceAction* const ca,
                       eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::CRA_collectFinish),
        mPtr(ca), mTile(tile) {}

    void call() override {
        if(!mTile) return;
        mTile->setBusy(false);
        if(!mPtr) return;
        const auto t = mPtr.get();
        t->callCollectedAction(mTile);
    }

    void read(eReadStream& src) override {
        mTile = src.readTile(board());
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mPtr = static_cast<eCollectResourceAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeTile(mTile);
        dst.writeCharacterAction(mPtr);
    }
private:
    stdptr<eCollectResourceAction> mPtr;
    eTile* mTile = nullptr;
};

class eCRA_collectFail : public eCharActFunc {
public:
    eCRA_collectFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::CRA_collectFail) {}
    eCRA_collectFail(eGameBoard& board, eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::CRA_collectFail),
        mTile(tile) {}

    void call() override {
        if(!mTile) return;
        mTile->setBusy(false);
    }

    void read(eReadStream& src) override {
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const override {
        dst.writeTile(mTile);
    }
private:
    eTile* mTile = nullptr;
};

class eCRA_callCollectedActionFinish : public eCharActFunc {
public:
    eCRA_callCollectedActionFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::CRA_callCollectedActionFinish) {}
    eCRA_callCollectedActionFinish(eGameBoard& board,
                                   eResourceCollectBuildingBase* const b) :
        eCharActFunc(board, eCharActFuncType::CRA_callCollectedActionFinish),
        mBptr(b) {}

    void call() override {
        if(!mBptr) return;
        mBptr->addRaw();
    }

    void read(eReadStream& src) override {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mBptr = static_cast<eResourceCollectBuildingBase*>(b);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeBuilding(mBptr);
    }
private:
    stdptr<eResourceCollectBuildingBase> mBptr;
};

#endif // ECOLLECTRESOURCEACTION_H
