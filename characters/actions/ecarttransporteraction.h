#ifndef ECARTTRANSPORTERACTION_H
#define ECARTTRANSPORTERACTION_H

#include "eactionwithcomeback.h"

#include "characters/ecarttransporter.h"
#include "buildings/ebuildingwithresource.h"

class eCartTransporterAction : public eActionWithComeback {
    friend class eCTA_findTargetFinish;
public:
    eCartTransporterAction(eCharacter* const c,
                           eBuildingWithResource* const b);
    eCartTransporterAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    eCartActionTypeSupport support() const;

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

#endif // ECARTTRANSPORTERACTION_H
