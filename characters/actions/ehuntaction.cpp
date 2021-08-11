#include "ehuntaction.h"

eHuntAction::eHuntAction(eResourceCollector* const c,
                         const eAction& failAction,
                         const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mCharacter(c), mTile(c->tile()) {}

void eHuntAction::increment(const int by) {
    (void)by;
    mCharacter->incCollected(100);
    setState(eCharacterActionState::finished);
}
