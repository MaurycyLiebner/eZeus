#ifndef EAPOLLOHELPACTION_H
#define EAPOLLOHELPACTION_H

#include "characters/actions/egodaction.h"

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
    eApolloHelpAct(eGameBoard& board) :
        eGodAct(board, eGodActType::apolloHelp) {}

    eTile* find(eTile* const t) {
        (void)t;
        return nullptr;
    }

    void act() {
        auto& board = eGodAct::board();
        const auto ps = board.plagues();
        for(const auto& p : ps) {
            board.healPlague(p);
        }
    }

    void read(eReadStream& src) {
        (void)src;
    }

    void write(eWriteStream& dst) const {
        (void)dst;
    }
};

#endif // EAPOLLOHELPACTION_H
