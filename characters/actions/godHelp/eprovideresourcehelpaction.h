#ifndef EPROVIDERESOURCEHELPACTION_H
#define EPROVIDERESOURCEHELPACTION_H

#include "characters/actions/egodaction.h"

enum class eProvideResourceHelpStage {
    none, appear, goTo, give, disappear
};

class eProvideResourceHelpAction : public eGodAction {
public:
    eProvideResourceHelpAction(eCharacter* const c,
                               const eCharActionType type,
                               const eResourceType res,
                               const int count);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board,
                            const eResourceType res,
                            const int minSpace);
private:
    eProvideResourceHelpStage mStage{eProvideResourceHelpStage::none};
    stdptr<eStorageBuilding> mTarget;
    eResourceType mResource = eResourceType::wheat;
    int mCount = 32;
};

class eGodProvideResourceAct : public eGodAct {
public:
    eGodProvideResourceAct(eGameBoard& board,
                           eStorageBuilding* const target,
                           const eResourceType resource,
                           const int count) :
        eGodAct(board, eGodActType::provideResource),
        mTarget(target),
        mResource(resource),
        mCount(count) {}

    eGodProvideResourceAct(eGameBoard& board) :
        eGodProvideResourceAct(board, nullptr, eResourceType::meat, 0) {}

    eTile* find(eTile* const t) {
        (void)t;
        return nullptr;
    }

    void act() {
        if(mTarget) {
            mTarget->add(mResource, mCount);
        }
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTarget = static_cast<eStorageBuilding*>(b);
        });
        src >> mResource;
        src >> mCount;
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mTarget);
        dst << mResource;
        dst << mCount;
    }
private:
    stdptr<eStorageBuilding> mTarget;
    eResourceType mResource;
    int mCount;
};


#endif // EPROVIDERESOURCEHELPACTION_H
