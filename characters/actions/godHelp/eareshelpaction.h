#ifndef EARESHELPACTION_H
#define EARESHELPACTION_H

#include "characters/actions/egodaction.h"

enum class eAresHelpStage {
    none, appear, go
};

class eAresHelpAction : public eGodAction {
public:
    eAresHelpAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board);
private:
    void goToTarget();

    eAresHelpStage mStage{eAresHelpStage::none};
};

#endif // EARESHELPACTION_H
