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

    void decCount(const int by);

    static bool sHelpNeeded(const eGameBoard& board,
                            const eResourceType res,
                            const int minSpace);
private:
    void goToTarget();
    void give();

    eProvideResourceHelpStage mStage{eProvideResourceHelpStage::none};
    stdptr<eStorageBuilding> mTarget;
    eResourceType mResource = eResourceType::wheat;
    int mCount = 32;
};

class eGodProvideResourceAct : public eGodAct {
public:
    eGodProvideResourceAct(eGameBoard& board,
                           eProvideResourceHelpAction* const action,
                           eStorageBuilding* const target,
                           const eResourceType resource,
                           const int count) :
        eGodAct(board, eGodActType::provideResource),
        mAction(action),
        mTarget(target),
        mResource(resource),
        mCount(count) {}

    eGodProvideResourceAct(eGameBoard& board) :
        eGodProvideResourceAct(board, nullptr, nullptr,
                               eResourceType::meat, 0) {}

    eMissileTarget find(eTile* const t) {
        (void)t;
        const auto null = static_cast<eTile*>(nullptr);
        return null;
    }

    void act() {
        if(mTarget) {
            const int added = mTarget->add(mResource, mCount);
            if(mAction) {
                mAction->decCount(added);
            }
        }
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTarget = static_cast<eStorageBuilding*>(b);
        });
        src >> mResource;
        src >> mCount;
        src.readCharacterAction(&board(), [this](eCharacterAction* const a) {
            mAction = static_cast<eProvideResourceHelpAction*>(a);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mTarget);
        dst << mResource;
        dst << mCount;
        dst.writeCharacterAction(mAction);
    }
private:
    stdptr<eProvideResourceHelpAction> mAction;
    stdptr<eStorageBuilding> mTarget;
    eResourceType mResource;
    int mCount;
};

#endif // EPROVIDERESOURCEHELPACTION_H
