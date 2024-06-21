#ifndef EHEPHAESTUSHELPACTION_H
#define EHEPHAESTUSHELPACTION_H

#include "characters/actions/egodaction.h"

enum class eHephaestusHelpStage {
    none, appear, provide, disappear
};

class eHephaestusHelpAction : public eGodAction {
public:
    eHephaestusHelpAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board);
private:
    void provide();

    eHephaestusHelpStage mStage{eHephaestusHelpStage::none};
};

#endif // EHEPHAESTUSHELPACTION_H
