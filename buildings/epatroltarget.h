#ifndef EPATROLTARGET_H
#define EPATROLTARGET_H

#include "epatrolbuilding.h"

class ePatrolTarget : public ePatrolBuilding {
    friend class ePT_spawnGetActorFinish;
public:
    ePatrolTarget(eGameBoard& board,
                  const eBuildingType fromBuilding,
                  const eBaseTex baseTex,
                  const double overlayX,
                  const double overlayY,
                  const eOverlays overlays,
                  const eCharGenerator& charGen,
                  const eBuildingType type,
                  const int sw, const int sh,
                  const int maxEmployees);

    bool available() const { return mAvailable > 0; }

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void spawnGetActor();

    const eBuildingType mFromBuilding;
    const eCharGenerator mCharGen;

    int mAvailable = -1;

    const int mAvailableWaitTime = 50000;
    const int mSpawnWaitTime = 20000;
    int mSpawnTime = 0;
    stdptr<eCharacter> mChar;
};

class ePT_spawnGetActorFinish : public eCharActFunc {
public:
    ePT_spawnGetActorFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::PT_spawnGetActorFinish) {}
    ePT_spawnGetActorFinish(eGameBoard& board, ePatrolTarget* const t) :
        eCharActFunc(board, eCharActFuncType::PT_spawnGetActorFinish),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->mAvailable = t->mAvailableWaitTime;
        t->setSpawnPatrolers(true);
    }

    void read(eReadStream& src) override {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTptr = static_cast<ePatrolTarget*>(b);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeBuilding(mTptr);
    }
private:
    stdptr<ePatrolTarget> mTptr;
};

#endif // EPATROLTARGET_H
