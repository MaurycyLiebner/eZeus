#ifndef EATLASHELPACTION_H
#define EATLASHELPACTION_H

#include "characters/actions/egodaction.h"

enum class eAtlasHelpStage {
    none, appear, goTo, give, disappear
};

class eAtlasHelpAction : public eGodAction {
public:
    eAtlasHelpAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board);
private:
    void goToTarget();
    void give();

    eAtlasHelpStage mStage{eAtlasHelpStage::none};
    stdptr<eSanctuary> mTarget;
};

class eAtlasHelpAct : public eGodAct {
public:
    eAtlasHelpAct(eGameBoard& board,
                  eSanctuary* const target) :
        eGodAct(board, eGodActType::atlasHelp),
        mTarget(target) {}

    eAtlasHelpAct(eGameBoard& board) :
        eAtlasHelpAct(board, nullptr) {}


    eTile* find(eTile* const t) {
        (void)t;
        return nullptr;
    }

    void act() {
        if(mTarget) {
            mTarget->add(eResourceType::wood, 8);
            mTarget->add(eResourceType::marble, 12);
            mTarget->add(eResourceType::sculpture, 4);
        }
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTarget = static_cast<eSanctuary*>(b);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mTarget);
    }
private:
    stdptr<eSanctuary> mTarget;
};

#endif // EATLASHELPACTION_H
