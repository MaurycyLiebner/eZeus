#ifndef EAPOLLOHELPACTION_H
#define EAPOLLOHELPACTION_H

#include "characters/actions/egodaction.h"

#include "buildings/esmallhouse.h"

enum class eApolloHelpStage {
    none, appear, goTo, heal, disappear
};

class eApolloHelpAction : public eGodAction {
public:
    eApolloHelpAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board);
private:
    void goToTarget();
    void heal();

    eApolloHelpStage mStage{eApolloHelpStage::none};
};

class eApolloHelpAct : public eGodAct {
public:
    eApolloHelpAct(eGameBoard& board,
                   eSmallHouse* const target) :
        eGodAct(board, eGodActType::apolloHelp),
        mTarget(target) {}

    eApolloHelpAct(eGameBoard& board) :
        eApolloHelpAct(board, nullptr) {}

    eMissileTarget find(eTile* const t) {
        (void)t;
        const auto null = static_cast<eTile*>(nullptr);
        return null;
    }

    void act() {
        auto& board = eGodAct::board();
        const auto p = board.plagueForHouse(mTarget);
        if(p) board.healPlague(p);
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTarget = static_cast<eSmallHouse*>(b);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mTarget);
    }
private:
    stdptr<eSmallHouse> mTarget;
};

#endif // EAPOLLOHELPACTION_H
