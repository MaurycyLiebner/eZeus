#ifndef ECARTTRANSPORTERACTION_H
#define ECARTTRANSPORTERACTION_H

#include "eactionwithcomeback.h"

#include "characters/ecarttransporter.h"
#include "buildings/ebuildingwithresource.h"

class eCartTransporterAction : public eActionWithComeback {
    friend class eCTA_findTargetFinish;
    friend class eCTA_waitOutsideFinish;
public:
    eCartTransporterAction(eCharacter* const c,
                           eBuildingWithResource* const b);
    eCartTransporterAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    eCartActionTypeSupport support() const;
    eResourceType supportsResource() const;

    bool waiting();
protected:
    void findTarget();
    void findTarget(const eCartTask& task);
    void findTarget(const std::vector<eCartTask>& tasks);
    void goBack();

    void targetResourceAction(const int bx, const int by);
    void targetResourceAction(eBuildingWithResource* const rb);
    bool targetProcessTask(eBuildingWithResource* const rb,
                           const eCartTask& task);

    void startResourceAction(const eCartTask& task);
    void finishResourceAction(const eCartTask& task);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void updateWaiting();

    void waitOutside();
    void spread();
    void clearTask();

    void disappear();

    eBuildingWithResource* mBuilding = nullptr;

    eCartTask mTask;

    int mUpdateWaiting = 0;

    bool mNoTarget = false;
    bool mWaitOutside = false;
};

class eCTA_findTargetFinish : public eCharActFunc {
public:
    eCTA_findTargetFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::CTA_findTargetFinish) {}
    eCTA_findTargetFinish(eGameBoard& board,
                          eCartTransporterAction* const ca) :
        eCharActFunc(board, eCharActFuncType::CTA_findTargetFinish),
        mTptr(ca) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->targetResourceAction(mBx, mBy);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eCartTransporterAction*>(ca);
        });
        src >> mBx;
        src >> mBy;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst << mBx;
        dst << mBy;
    }

    void setXY(const int x, const int y) {
        mBx = x;
        mBy = y;
    }
private:
    stdptr<eCartTransporterAction> mTptr;
    int mBx = -1;
    int mBy = -1;
};

class eCTA_waitOutsideFinish : public eCharActFunc {
public:
    eCTA_waitOutsideFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::CTA_waitOutsideFinish) {}
    eCTA_waitOutsideFinish(eGameBoard& board,
                           eCartTransporterAction* const ca) :
        eCharActFunc(board, eCharActFuncType::CTA_waitOutsideFinish),
        mTptr(ca) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->spread();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eCartTransporterAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eCartTransporterAction> mTptr;
};

class eCTA_spreadFinish : public eCharActFunc {
public:
    eCTA_spreadFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::CTA_spreadFinish) {}
    eCTA_spreadFinish(eGameBoard& board, eCharacter* const c) :
        eCharActFunc(board, eCharActFuncType::CTA_spreadFinish),
        mCptr(c) {}

    void call() override {
        if(!mCptr) return;
        const auto c = mCptr.get();
        c->setActionType(eCharacterActionType::stand);
    }

    void read(eReadStream& src) override {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacter(mCptr);
    }
private:
    stdptr<eCharacter> mCptr;
};

#endif // ECARTTRANSPORTERACTION_H
