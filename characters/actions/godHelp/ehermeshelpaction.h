#ifndef EHERMESHELPACTION_H
#define EHERMESHELPACTION_H

#include "characters/actions/egodaction.h"

enum class eHermesHelpStage {
    none, appear, provide, disappear
};

class eHermesHelpAction : public eGodAction {
public:
    eHermesHelpAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static bool sHelpNeeded(const eGameBoard& board);
private:
    void provide();

    eHermesHelpStage mStage{eHermesHelpStage::none};
};

#endif // EHERMESHELPACTION_H
