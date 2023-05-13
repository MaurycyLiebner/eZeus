#ifndef EHERAHELPACTION_H
#define EHERAHELPACTION_H

#include "characters/actions/egodaction.h"

#include "buildings/eagorabase.h"

enum class eHeraHelpStage {
    none, appear, goTo, give, disappear
};

class eHeraHelpAction : public eGodAction {
public:
    eHeraHelpAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board);
private:
    void goToTarget();
    void give();

    eHeraHelpStage mStage{eHeraHelpStage::none};
    stdptr<eAgoraBase> mTarget;
    std::vector<stdptr<eAgoraBase>> mFutureTargets;
};

class eGodProvideAgoraAct : public eGodAct {
public:
    eGodProvideAgoraAct(eGameBoard& board,
                        eAgoraBase* const target) :
        eGodAct(board, eGodActType::provideAgora),
        mTarget(target) {}

    eGodProvideAgoraAct(eGameBoard& board) :
        eGodProvideAgoraAct(board, nullptr) {}

    eTile* find(eTile* const t) {
        (void)t;
        return nullptr;
    }

    void act() {
        if(mTarget) {
            mTarget->add(eResourceType::food, 8);
            mTarget->add(eResourceType::fleece, 8);
            mTarget->add(eResourceType::oliveOil, 8);
            mTarget->add(eResourceType::wine, 8);
        }
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTarget = static_cast<eAgoraBase*>(b);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mTarget);
    }
private:
    stdptr<eAgoraBase> mTarget;
};

#endif // EHERAHELPACTION_H
